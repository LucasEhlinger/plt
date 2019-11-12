#include <iostream>
#include <array>
#include <unistd.h>
#include "render.h"
#include <string.h>

// Those lines have for sole purpose to check if the SFML is working properly
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

void testSFML() {
    sf::Texture texture;
}
// End SFML test

using namespace std;
using namespace render;

int testRender();

void parse(int nb_row, int nb_col, unsigned int raw_table[], unsigned int table[]);

int main(int argc, char *argv[]) {
    testRender();
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

    const int screen_width = 1536;
    const int screen_height = 860;
    const int tile_width = 72;
    const int tile_height = 84;
    const int nb_col = 13;
    const int nb_row = 13;
    unsigned int tiles[nb_col * nb_row];
    unsigned int level[nb_col * nb_row];
    unsigned int table[nb_col * nb_row];

    // create the window
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "just_another_plt_map");

    render::Scene scene{};
    scene.draw(tiles);

    parse(nb_row, nb_col, tiles, level);
    // create the tilemap from the level definition
    TileMap tile_map;
    if (!tile_map.load("./../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level, nb_col,
                       nb_row))
        return -1;

    unsigned int pawn_pos[] = {
            9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 1,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 5, 4, 5, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 6, 9, 9, 9, 9, 9,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
            2, 9, 9, 9, 9, 9, 3, 9, 9, 9, 9, 9, 9,
    };

    parse(nb_row, nb_col, pawn_pos, table);

    PawnMap pawn_map;
    if (!pawn_map.load("./../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), table, nb_row, nb_col))
        return -1;

    // run the main loop
    while (window.isOpen()) {
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
        usleep(5000);
    }

    return 0;
}

void parse(int nb_row, int nb_col, unsigned int raw_table[], unsigned int table[]) {
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
