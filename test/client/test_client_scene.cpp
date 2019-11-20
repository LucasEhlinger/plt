
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include <state.h>
#include "../../src/client/render/Scene.h"

BOOST_AUTO_TEST_CASE(TestSceneValues) {
    state::Start st{};
    state::Field fi{};
    state::Board board{};
    board.generate();
    board.pawns.push_back(state::Player{state::Coordinate{0, 6}, "test1", false});

    render::Scene scene{board};
    auto tiles = scene.matrixTile();

    BOOST_CHECK_EQUAL(tiles[6], st.number_type);
    BOOST_CHECK_EQUAL(tiles[7], fi.number_type);
    BOOST_CHECK_EQUAL(tiles[18], fi.number_type);
    BOOST_CHECK_EQUAL(tiles[19], fi.number_type);
    BOOST_CHECK(scene.pawnsView.front()->pawn == board.pawns.front());
}

BOOST_AUTO_TEST_CASE(TestPawnsValue) {
    state::Board board{};
    board.generate();

    state::King king{state::Coordinate{6, 6}};
    king.number_type = 4;
    state::Player player1{state::Coordinate{0, 6}, "test1", false};
    player1.number_type = 1;

    board.pawns.push_back(king);
    board.pawns.push_back(player1);

    render::Scene scene{board};

    auto map = scene.matrixPawn();
    BOOST_CHECK_EQUAL(map[king.getCoordinate().getCoordInLine()], king.number_type);
    BOOST_CHECK_EQUAL(map[player1.getCoordinate().getCoordInLine()], player1.number_type);

}