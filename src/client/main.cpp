#include <iostream>
#include <array>
#include <unistd.h>
#include "render.h"
#include <string.h>
#include "engine.h"
#include "state.h"

// Those lines have for sole purpose to check if the SFML is working properly
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace render;

int testRender();

void parse(int nb_row, int nb_col, unsigned int raw_table[], unsigned int table[]);

void parse(int nb_row, int nb_col, std::array<int, 169> raw_table, unsigned int table[]);

int main(int argc, char *argv[]) {
    //testRender();
    if (argc == 2) {
        if (strcmp(argv[1], "hello") == 0) {
            cout << "Bonjour à tous !" << endl;
        } else if (strcmp(argv[1], "render") == 0) {
            testRender();
        } else if (strcmp(argv[1], "engine") == 0) {

        }
    } else {
        cout << "Je n'ai pas compris, entrez une de ces commandes :" << endl;
        cout << "hello, render, engine" << endl;
    }
    return 0;
}

int testRender() {

    const int tile_width = 72;
    const int tile_height = 84;
    const int nb_col = 13;
    const int nb_row = 13;
    unsigned int level[nb_col * nb_row];
    unsigned int table[nb_col * nb_row];

    // create the window
    sf::RenderWindow window(sf::VideoMode(1536, 860), "just_another_plt_map");

    state::Board board{};
    board.generate();
    engine::Engine engine1{board};
    render::Scene scene{board};


    parse(nb_row, nb_col, scene.draw(), level);

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

        if (i > 2000 && i < 2500) {
            engine1.move(board.pawns[1], state::Coordinate{0, 7});
            board.pawns.front().notify();
        } else if (i > 3000 && i < 3500) {
            engine1.move(board.pawns[1], state::Coordinate{1, 7});
            board.pawns.front().notify();
        } else if (i > 4000 && i < 4500) {
            engine1.move(board.pawns[1], state::Coordinate{1, 8});
            board.pawns.front().notify();
        } else if (i > 5000 && i < 5500) {
            engine1.move(board.pawns[1], state::Coordinate{2, 7});
            board.pawns.front().notify();
        } else if (i > 6000 && i < 6500) {
            engine1.move(board.pawns[1], state::Coordinate{3, 7});
            board.pawns.front().notify();
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

void parse(int nb_row, int nb_col, std::array<int, 169> raw_table, unsigned int table[]) {
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
