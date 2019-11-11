#include <boost/test/unit_test.hpp>

#include <iostream>
#include <array>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string.h>
#include "../../src/client/render.h"

using namespace std;


BOOST_AUTO_TEST_CASE(TestLoad) {
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
    render::TileMap map;
    BOOST_CHECK(map.load("../../../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level,
                         nb_col,
                         nb_row));
    BOOST_CHECK(!map.load("../../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level,
                          nb_col,
                          nb_row));
}

/*BOOST_AUTO_TEST_CASE(TestFailLoad) {
    {
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
        render::TileMap map;
        BOOST_CHECK(!map.load("../../res/hexagon-pack/PNG/tileset.png", sf::Vector2u(tile_width, tile_height), level,
                              nb_col,
                              nb_row));
    }
}*/