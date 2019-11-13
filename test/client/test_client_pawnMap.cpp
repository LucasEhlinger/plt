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
    const int tile_width = 72;
    const int tile_height = 84;
    const int nb_col = 13;
    const int nb_row = 13;
    unsigned int tiles[nb_col * nb_row];
    unsigned int level[nb_col * nb_row];
    unsigned int table[nb_col * nb_row];

    state::Board board{};
    board.generate();

    render::Scene scene{board};

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

    for (int i = 0; i < nb_row; ++i) {
        int blanks = abs((nb_row - 1) / 2 - i);
        int blanks_even = blanks % 2;
        for (int j = 0; j < nb_col; ++j) {
            if (j < (blanks + blanks_even) / 2)
                table[i * nb_row + j] = 9;
            else if (j >= nb_col - blanks + (blanks + blanks_even) / 2)
                table[i * nb_row + j] = 9;
            else if (i < (nb_row - 1) / 2)
                table[i * nb_row + j] = pawn_pos[i * nb_row + j + (blanks - blanks_even) / 2];
            else
                table[i * nb_row + j] = pawn_pos[i * nb_row + j - (blanks + blanks_even) / 2];
        }
    }

    // create the pawnMap from the level definition
    render::PawnMap pawn_map;
    BOOST_CHECK (pawn_map.load("../../../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), table, nb_row, nb_col));
    BOOST_CHECK (!pawn_map.load("../../res/pawn/pawnset.png", sf::Vector2u(tile_width, tile_height), table, nb_row, nb_col));


}