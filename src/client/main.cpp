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

int main(int argc, char *argv[]) {
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

    // create the window
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "just_another_plt_map");

    render::Scene scene{};
    scene.draw(tiles);
    for (int i = 0; i < nb_row; ++i) {
        int blanks = abs((nb_row - 1) / 2 - i);
        int blanks_even = blanks % 2;
        for (int j = 0; j < nb_col; ++j) {
            if (j < (blanks + blanks_even) / 2)
                level[i * nb_row + j] = 9;
            else if (j >= nb_col - blanks + (blanks + blanks_even) / 2)
                level[i * nb_row + j] = 9;
            else if (i < (nb_row - 1) / 2)
                level[i * nb_row + j] = tiles[i * nb_row + j + (blanks - blanks_even) / 2];
            else
                level[i * nb_row + j] = tiles[i * nb_row + j - (blanks + blanks_even) / 2];
        }
    }

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("./../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level, nb_col,
                  nb_row))
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
        window.draw(map);
        window.display();
        usleep(5000);
    }

    return 0;
}
