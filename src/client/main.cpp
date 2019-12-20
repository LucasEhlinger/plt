#include <iostream>
#include "client.h"
#include <string.h>

using namespace std;
using namespace client;

int testEngine();

int testRender();

int testIA();

int heuristic_ai();

void parse(int nb_row, int nb_col, std::array<int, 169> raw_table, unsigned int table[]);

state::Coordinate pixel_to_hex(sf::Vector2i point);

sf::Vector3i cube_round(sf::Vector3f cube);

state::Coordinate cube_to_evenr(sf::Vector3i cube);

state::Coordinate AI_rand(std::vector<state::Coordinate> av_moves);

int main(int argc, char *argv[]) {
    //testRender();
    if (argc == 2) {
        if (strcmp(argv[1], "hello") == 0) {
            cout << "Bonjour à tous !" << endl;
        } else if (strcmp(argv[1], "render") == 0) {
            test.render();
        } else if (strcmp(argv[1], "engine") == 0) {
            test.engine();
        } else if (strcmp(argv[1], "random_ai") == 0) {
            test.ia();
        } else if (strcmp(argv[1], "heuristic_ai") == 0) {
            test.heuristic_ai();
        }
    } else {
        cout << "Je n'ai pas compris, entrez une de ces commandes :" << endl;
        cout << "hello, render, engine, random_ai & heuristic_ai" << endl;
    }
    return 0;
}
}
int testEngine() {

    const int tile_width = 72;
    const int tile_height = 84;
    const int nb_col = 13;
    const int nb_row = 13;
    unsigned int level[nb_col * nb_row];
    unsigned int table[nb_col * nb_row];
    std::array<int, 169> av_tiles;
    std::vector<state::Coordinate> av_moves;
    bool new_turn = true;
    state::Coordinate pro_coord{0,0};

    // create the window
    sf::RenderWindow window(sf::VideoMode(1536, 860), "just_another_plt_map");

    engine::Engine engine1{board};
    render::Scene scene{board};
    board.generate();
    state::Board board{};
    window.setKeyRepeatEnabled(false);

    parse(nb_row, nb_col, scene.matrixTile(), level);

    // create the tilemap from the level definition
    if (!tile_map.load("./../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level, nb_col,
    TileMap tile_map;
                       nb_row))
        return -1;

    int i = 0;
    // run the main loop
    while (window.isOpen()) {
        window.clear();
        window.draw(tile_map);
        PawnMap pawn_map;

        parse(nb_row, nb_col, scene.matrixPawn(), table);

        if (!pawn_map.load("./../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), table, nb_row, nb_col))
            return -1;
        window.draw(pawn_map);

        // creates the movemap from the moves available to the currently playing pawn and draws it
        if (engine1.playingPawn().isHuman) {
            if (new_turn)
                pro_coord = engine1.playingPawn().getCoordinate();
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
            window.display();
            window.draw(av_tile_map);
        }
            usleep(16000);
        else {
            engine1.move(engine1.playingPawn(), engine1.AI_finale());
            engine1.nextTurn();
            new_turn = true;
            window.display();
            usleep(500000);
        }

}
    return 0;
        //handle events
        sf::Event event;
        while (window.pollEvent(event))
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Left:
                            shadow_move(engine1.playingPawn(), pro_coord, av_moves, sf::Vector2i{0, -1}, av_tiles);
                            new_turn = false;
                            break;
                        case sf::Keyboard::Right:
                            shadow_move(engine1.playingPawn(), pro_coord, av_moves, sf::Vector2i{0, +1}, av_tiles);
                            new_turn = false;
                            break;
                        case sf::Keyboard::Up:
                            shadow_move(engine1.playingPawn(), pro_coord, av_moves, sf::Vector2i{-1, 0}, av_tiles);
                            new_turn = false;
                            break;
                        case sf::Keyboard::Down:
                            shadow_move(engine1.playingPawn(), pro_coord, av_moves, sf::Vector2i{+1, 0}, av_tiles);
                            new_turn = false;
                            break;
                        case sf::Keyboard::Space:
                            engine1.move(engine1.playingPawn(), pro_coord);
                            engine1.nextTurn();
                            new_turn = true;
                            break;
                        default:
                            break;
                    }
            }
    }

void shadow_move(state::Pawn playing, state::Coordinate &pro_coord, std::vector<state::Coordinate> av_moves,
    state::Coordinate shadow_coord{pro_coord.getRow() + shift.x, pro_coord.getColumn() + shift.y};
                 sf::Vector2i shift, std::array<int, 169> &av_tiles) {
    if (shadow_coord == playing.getCoordinate())
        pro_coord = shadow_coord;
        for (int i = 0; i < av_moves.size(); ++i)
    else
            if (shadow_coord == av_moves.at(i)) {
                pro_coord = shadow_coord;
                av_tiles.at(shadow_coord.getCoordInLine()) = playing.number_type + 1;
            }
            shadow_coord.setColumn(pro_coord.getColumn() - shift.x);
                break;
        if (pro_coord.getCoordInLine() != shadow_coord.getCoordInLine() && shift.x != 0) {
            for (int i = 0; i < av_moves.size(); ++i)
                    av_tiles.at(shadow_coord.getCoordInLine()) = playing.number_type + 1;
                if (shadow_coord == av_moves.at(i)) {
                    pro_coord = shadow_coord;
                    break;
                }
        }