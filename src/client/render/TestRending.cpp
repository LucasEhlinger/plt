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

using namespace render;

TestRending::TestRending() {

}

int TestRending::render() {
    unsigned int level[nb_col * nb_row];
    unsigned int table[nb_col * nb_row];

    // create the window
    sf::RenderWindow window(sf::VideoMode(1536, 860), "just_another_plt_map");

    state::Board board{};
    board.generate();
    render::Scene scene{board};


    parse(nb_row, nb_col, scene.matrixTile(), level);

    // create the tilemap from the level definition
    TileMap tile_map;
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
    unsigned int level[nb_col * nb_row];
    unsigned int table[nb_col * nb_row];

    // create the window
    sf::RenderWindow window(sf::VideoMode(1536, 860), "just_another_plt_map");

    state::Board board{};
    board.generate();
    engine::Engine engine1{board};
    render::Scene scene{board};


    parse(nb_row, nb_col, scene.matrixTile(), level);

    // create the tilemap from the level definition
    TileMap tile_map;
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
                state::Coordinate pos = pixel_to_hex(sf::Mouse::getPosition(window));
                engine1.move(engine1.playingPawn(), pos);
                engine1.nextTurn();
            }
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

int TestRending::ia() {
    unsigned int level[nb_col * nb_row];
    unsigned int table[nb_col * nb_row];
    std::array<int, 169> av_tiles;
    std::vector<state::Coordinate> av_moves;

    // create the window
    sf::RenderWindow window(sf::VideoMode(1536, 860), "just_another_plt_map");

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


        engine1.move(engine1.playingPawn(), ai.action(av_moves));
        engine1.nextTurn();

    }

    return 0;
}

int TestRending::heuristic_ai() {
    unsigned int level[nb_col * nb_row];
    unsigned int table[nb_col * nb_row];
    std::array<int, 169> av_tiles;
    std::vector<state::Coordinate> av_moves;

    // create the window
    sf::RenderWindow window(sf::VideoMode(1536, 860), "just_another_plt_map");

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

        engine1.move(engine1.playingPawn(), engine1.AI_finale());
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

state::Coordinate TestRending::pixel_to_hex(sf::Vector2i point) {
    float q = (sqrt(3) / 3 * point.x - 1. / 3 * point.y) / 42;
    float r = (2. / 3 * point.y) / 42;
    return cube_to_evenr(cube_round(sf::Vector3f{q, -q - r, r}));
}

state::Coordinate TestRending::cube_to_evenr(sf::Vector3i cube) {
    int col = cube.x + (cube.z + (cube.z & 1)) / 2;
    int row = cube.z;
    return state::Coordinate{row, col};
}

sf::Vector3i TestRending::cube_round(sf::Vector3f cube) {
    int rx = round(cube.x);
    int ry = round(cube.y);
    int rz = round(cube.z);

    float x_diff = abs(rx - cube.x);
    float y_diff = abs(ry - cube.y);
    float z_diff = abs(rz - cube.z);

    if (x_diff > y_diff && x_diff > z_diff)
        rx = -ry - rz;
    else if (y_diff > z_diff)
        ry = -rx - rz;
    else
        rz = -rx - ry;

    return sf::Vector3i{rx, ry, rz};
}