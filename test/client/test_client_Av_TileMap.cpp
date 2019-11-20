#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include "../../src/client/render.h"

BOOST_AUTO_TEST_CASE(TestInit) {
    {
        const int tile_width = 72;
        const int tile_height = 84;
        const int nb_col = 13;
        const int nb_row = 13;
        unsigned int table[nb_col * nb_row];
        std::array<int, 169> av_tiles;
        std::vector<state::Coordinate> av_moves;

        render::Av_TileMap av_tile_map;
        
        BOOST_CHECK(av_tile_map.load("../../../res/hexagon-pack/PNG/av_move.png", sf::Vector2u(tile_width, tile_height), table, nb_row, nb_col));
        BOOST_CHECK(!av_tile_map.load("./../res/hexagon-pack/PNG/av_move.png", sf::Vector2u(tile_width, tile_height), table, nb_row, nb_col));
    }
}