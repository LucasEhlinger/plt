#include "TestRending.h"
#include "engine.h"
#include "ai.h"
#include <iostream>
#include <array>
#include <unistd.h>
#include <string.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../render.h"

using namespace render;
using namespace client;
using namespace sf;

TestRending::TestRending() : window(VideoMode(1536, 860), "just_another_plt_map") {
}

int TestRending::render() {
    state::Board board{};
    board.generate();
    render::Scene scene{board};


    parse(nb_row, nb_col, scene.matrixTile(), level);

    // create the tilemap from the level definition
    render::TileMap tile_map;
    if (!tile_map.load("./../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level, nb_col,
                       nb_row))
        return -1;

    int i = 0;
    // run the main loop
    while (window.isOpen()) {
        ++i;
        PawnMap pawn_map;
        parse(nb_row, nb_col, scene.matrixPawn(), table);

        if (!pawn_map.load("./../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), table, nb_row, nb_col))
            return -1;

        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        window.draw(tile_map);
        window.draw(pawn_map);
        window.display();
        usleep(500);
    }
    return 0;
}

int TestRending::engine() {
    std::array<int, 169> av_tiles;
    std::vector<state::Coordinate> av_moves;
    std::vector<state::Coordinate> path;
    state::Coordinate pro_coord{0, 0};
    bool new_move = true;
    bool new_turn = true;
    std::vector<int> deaths;
    int ind_death_max;
    int ind_in_deaths;

    // sets up the window
    window.setKeyRepeatEnabled(false);
    state::Board board{};
    board.generate();
    engine::Engine engine1{board};
    render::Scene scene{board};

    sf::Font font;
    if (!font.loadFromFile("./../res/fonts/KingthingsPetrock.ttf"))
        return -1;

    parse(nb_row, nb_col, scene.matrixTile(), level);

    // create the tilemap from the level definition
    TileMap tile_map;
    if (!tile_map.load("./../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level, nb_col,
                       nb_row))
        return -1;

    // run the main loop
    while (window.isOpen()) {
        ind_death_max = 0;
        window.clear();
        window.draw(tile_map);

        PawnMap pawn_map;
        parse(nb_row, nb_col, scene.matrixPawn(), table);

        if (!pawn_map.load("./../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), table, nb_row, nb_col))
            return -1;
        window.draw(pawn_map);

        // creates the movemap from the moves available to the currently playing pawn and draws it
        if (engine1.playingPawn().isHuman) {
            if (new_move || new_turn) {
                pro_coord = engine1.playingPawn().getCoordinate();
                new_turn = false;
            }
            av_moves = engine1.matrixAv_Tile(engine1.playingPawn());
            av_tiles.fill(9);
            for (int j = 0; j < av_moves.size(); ++j)
                av_tiles.at(av_moves.at(j).getCoordInLine()) = 0;
            av_tiles.at(pro_coord.getCoordInLine()) = engine1.playingPawn().number_type + 1;

            parse(nb_row, nb_col, av_tiles, table);
            Av_TileMap av_tile_map;
            if (!av_tile_map.load("./../res/hexagon-pack/PNG/av_move.png", sf::Vector2u(tile_width, tile_height), table,
                                  nb_row, nb_col))
                return -1;
            window.draw(av_tile_map);
            window.display();
            usleep(16000);
        } else if (engine1.playingPawn().number_type == 4) {
            engine1.nextTurn();
            new_turn = true;
            window.display();
            usleep(16000);
        } else if (engine1.playingPawn().number_type == 5) {
            if (new_turn) {
                path = engine1.guard_behaviour();
                new_turn = false;
            }
            if (engine1.playingPawn().getAP() == 0 || path.empty()) {
                engine1.nextTurn();
                new_turn = true;
            } else {
                deaths = engine1.move(path.back());
                while (deaths.size() != 0) {
                    for (int i = 0; i < deaths.size(); ++i)
                        if (deaths.at(i) >= ind_death_max) {
                            ind_death_max = deaths.at(i);
                            ind_in_deaths = i;
                        }
                    scene.removing_pawn(board, ind_death_max);
                    deaths.erase(deaths.begin() + ind_in_deaths);
                    new_turn = true;
                }
                path.pop_back();
            }
            window.display();
            usleep(500000);
        } else if (engine1.playingPawn().number_type == 6) {
            if (new_turn) {
                path = engine1.bane_behaviour();
                new_turn = false;
            }
            if (engine1.playingPawn().getAP() == 0 || path.empty()) {
                engine1.nextTurn();
                new_turn = true;
            } else {
                deaths = engine1.move(path.back());
                while (deaths.size() != 0) {
                    for (int i = 0; i < deaths.size(); ++i)
                        if (deaths.at(i) >= ind_death_max) {
                            ind_death_max = deaths.at(i);
                            ind_in_deaths = i;
                        }
                    scene.removing_pawn(board, ind_death_max);
                    deaths.erase(deaths.begin() + ind_in_deaths);
                    new_turn = true;
                }
                path.pop_back();
            }
            window.display();
            usleep(500000);
        } else {
            if (new_turn) {
                path = engine1.AI_finale();
                new_turn = false;
            }
            if (path.size() != 0) {
                deaths = engine1.move(path.back());
                if (deaths.size() != 0)
                    for (int index : deaths)
                        scene.removing_pawn(board, index);
                path.pop_back();
            } else
                engine1.move(ai::Random::action(engine1.matrixAv_Tile(engine1.playingPawn())));
            if (engine1.playingPawn().getAP() == 0) {
                engine1.nextTurn();
                new_turn = true;
            }
            window.display();
            usleep(500000);
        }

        //handle events
        sf::Event event;
        while (window.pollEvent(event))
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Left:
                            if (engine1.playingPawn().isHuman) {
                                shadow_move(engine1.playingPawn(), pro_coord, av_moves, sf::Vector2i{0, -1}, av_tiles);
                                new_move = false;
                            }
                            break;
                        case sf::Keyboard::Right:
                            if (engine1.playingPawn().isHuman) {
                                shadow_move(engine1.playingPawn(), pro_coord, av_moves, sf::Vector2i{0, +1}, av_tiles);
                                new_move = false;
                            }
                            break;
                        case sf::Keyboard::Up:
                            if (engine1.playingPawn().isHuman) {
                                shadow_move(engine1.playingPawn(), pro_coord, av_moves, sf::Vector2i{-1, 0}, av_tiles);
                                new_move = false;
                            }
                            break;
                        case sf::Keyboard::Down:
                            if (engine1.playingPawn().isHuman) {
                                shadow_move(engine1.playingPawn(), pro_coord, av_moves, sf::Vector2i{+1, 0}, av_tiles);
                                new_move = false;
                            }
                            break;
                        case sf::Keyboard::Space:
                            if (engine1.playingPawn().isHuman) {
                                if (pro_coord == engine1.playingPawn().getCoordinate())
                                    break;
                                deaths = engine1.move(pro_coord);
                                while (deaths.size() != 0) {
                                    for (int i = 0; i < deaths.size(); ++i)
                                        if (deaths.at(i) >= ind_death_max) {
                                            ind_death_max = deaths.at(i);
                                            ind_in_deaths = i;
                                        }
                                    scene.removing_pawn(board, ind_death_max);
                                    deaths.erase(deaths.begin() + ind_in_deaths);
                                    new_turn = true;
                                }
                                new_move = true;
                            }
                            break;
                        case sf::Keyboard::P:
                            if (engine1.playingPawn().isHuman) {
                                engine1.nextTurn();
                                new_move = true;
                                new_turn = true;
                            }
                            break;
                        default:
                            break;
                    }
            }
    }

    return 0;
}

int TestRending::ia() {
    std::array<int, 169> av_tiles;
    std::vector<state::Coordinate> av_moves;

    ai::Random ai;

    state::Board board{};
    board.generate();
    engine::Engine engine1{board};
    render::Scene scene{board};

    window.clear();

    // creates the tilemap from the level definition and draws it
    parse(nb_row, nb_col, scene.matrixTile(), level);
    TileMap tile_map;
    if (!tile_map.load("./../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level, nb_col,
                       nb_row))
        return -1;
    window.draw(tile_map);

    // creates the pawnmap from the level defnition and draws it
    parse(nb_row, nb_col, scene.matrixPawn(), level);
    PawnMap pawn_map;
    if (!pawn_map.load("./../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), level, nb_row, nb_col))
        return -1;
    window.draw(pawn_map);

    window.display();

    // run the main loop
    while (window.isOpen()) {

        engine1.playingPawn().setAP(1);

        // creates the movemap from the moves available to the currently playing pawn and draws it
        av_moves = engine1.matrixAv_Tile(engine1.playingPawn());
        av_tiles.fill(9);
        for (int j = 0; j < av_moves.size(); ++j)
            av_tiles.at(av_moves.at(j).getCoordInLine()) = 0;

        parse(nb_row, nb_col, av_tiles, table);
        Av_TileMap av_tile_map;
        if (!av_tile_map.load("./../res/hexagon-pack/PNG/av_move.png", sf::Vector2u(tile_width, tile_height), table,
                              nb_row, nb_col))
            return -1;



        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        parse(nb_row, nb_col, scene.matrixPawn(), level);
        PawnMap pawn_map;
        if (!pawn_map.load("./../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), level, nb_row, nb_col))
            return -1;

        // draw the map
        window.clear();
        window.draw(tile_map);
        window.draw(av_tile_map);
        usleep(500000);
        window.draw(pawn_map);
        window.display();


        //engine1.move(engine1.playingPawn(), ai.action(av_moves));
        engine1.nextTurn();

    }

    return 0;
}

int TestRending::heuristic_ai() {
    std::array<int, 169> av_tiles;
    std::vector<state::Coordinate> av_moves;

    state::Board board{};
    board.generate();
    engine::Engine engine1{board};
    render::Scene scene{board};

    window.clear();

    // creates the tilemap from the level definition and draws it
    parse(nb_row, nb_col, scene.matrixTile(), level);
    TileMap tile_map;
    if (!tile_map.load("./../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level, nb_col,
                       nb_row))
        return -1;
    window.draw(tile_map);

    // creates the pawnmap from the level defnition and draws it
    parse(nb_row, nb_col, scene.matrixPawn(), level);
    PawnMap pawn_map;
    if (!pawn_map.load("./../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), level, nb_row, nb_col))
        return -1;
    window.draw(pawn_map);

    window.display();

    // run the main loop
    while (window.isOpen()) {

        engine1.playingPawn().setAP(1);

        // creates the movemap from the moves available to the currently playing pawn and draws it
        av_moves = engine1.matrixAv_Tile(engine1.playingPawn());
        av_tiles.fill(9);
        for (int j = 0; j < av_moves.size(); ++j)
            av_tiles.at(av_moves.at(j).getCoordInLine()) = 0;

        parse(nb_row, nb_col, av_tiles, table);
        Av_TileMap av_tile_map;
        if (!av_tile_map.load("./../res/hexagon-pack/PNG/av_move.png", sf::Vector2u(tile_width, tile_height), table,
                              nb_row, nb_col))
            return -1;

        //window.display();


        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        parse(nb_row, nb_col, scene.matrixPawn(), level);
        PawnMap pawn_map;
        if (!pawn_map.load("./../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), level, nb_row, nb_col))
            return -1;

        // draw the map
        window.clear();
        window.draw(tile_map);
        window.draw(av_tile_map);
        usleep(500000);
        window.draw(pawn_map);
        window.display();

       // engine1.move(engine1.playingPawn(), engine1.AI_finale().at(0));
        engine1.nextTurn();

    }

    return 0;
}


void TestRending::parse(int nb_row, int nb_col, std::array<int, 169> raw_table, unsigned int *table) {
    for (int i = 0; i < nb_row; ++i) {
        int blanks = abs((nb_row - 1) / 2 - i);
        int blanks_even = blanks % 2;
        for (int j = 0; j < nb_col; ++j) {
            if (j < (blanks + blanks_even) / 2)
                table[i * nb_row + j] = 9;
            else if (j >= nb_col - blanks + (blanks + blanks_even) / 2)
                table[i * nb_row + j] = 9;
            else if (i < (nb_row - 1) / 2)
                table[i * nb_row + j] = raw_table[i * nb_row + j + (blanks - blanks_even) / 2];
            else
                table[i * nb_row + j] = raw_table[i * nb_row + j - (blanks + blanks_even) / 2];
        }
    }
}

void
TestRending::shadow_move(state::Pawn playing, state::Coordinate &pro_coord, std::vector<state::Coordinate> av_moves,
                         sf::Vector2i shift, std::array<int, 169> &av_tiles) {
    state::Coordinate shadow_coord{pro_coord.getRow() + shift.x, pro_coord.getColumn() + shift.y};
    if (shadow_coord == playing.getCoordinate())
        shadow_coord.setColumn(shadow_coord.getColumn() - shift.x + shift.y);
    for (int i = 0; i < av_moves.size(); ++i)
        if (shadow_coord == av_moves.at(i)) {
            av_tiles.at(shadow_coord.getCoordInLine()) = playing.number_type + 1;
            pro_coord = shadow_coord;
            break;
        }
    if (pro_coord.getCoordInLine() != shadow_coord.getCoordInLine() && shift.x != 0) {
        shadow_coord.setColumn(pro_coord.getColumn() - shift.x);
        for (int i = 0; i < av_moves.size(); ++i)
            if (shadow_coord == av_moves.at(i)) {
                av_tiles.at(shadow_coord.getCoordInLine()) = playing.number_type + 1;
                pro_coord = shadow_coord;
                break;
            }
    }
}
