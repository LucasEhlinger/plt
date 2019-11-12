#include <boost/test/unit_test.hpp>
#include "state.h"
#include "../../src/client/render.h"

using namespace ::state;
using namespace ::render;

BOOST_AUTO_TEST_CASE(TestPawnObservable) {
    {
        Pawn pawn{Coordinate{11, 5}, "pawn"};
        PawnView pawnView{pawn};
        pawn.addObserver(&pawnView);
        BOOST_CHECK_EQUAL(pawnView.pawn.getAP(), 0);

        pawn.setAP(12);
        BOOST_CHECK_EQUAL(pawnView.pawn.getAP(), 0);
        pawn.notify();

        BOOST_CHECK_EQUAL(pawnView.pawn.getAP(), 12);
    }
}

BOOST_AUTO_TEST_CASE(TestBoardObservable) {
    {
        Board bo{};
        BoardView boardView{bo};
        bo.addObserver(&boardView);
        BOOST_CHECK(boardView.board.day);
        bo.changeTime();
        bo.notify();
        BOOST_CHECK(!boardView.board.day);
    }
}

BOOST_AUTO_TEST_CASE(TestTileObservable) {
    {
        Castle ca{};
        TileView tileView(ca);
        ca.addObserver(&tileView);
        ca.notify();
        BOOST_CHECK(ca == tileView.tile);
    }
}


BOOST_AUTO_TEST_CASE(TestAddAndRemove) {
    {
        Tile tile{};
        TileView tileView1{tile};
        TileView tileView2{tile};
        TileView tileView3{tile};
        tile.addObserver(&tileView1);
        tile.addObserver(&tileView2);
        tile.addObserver(&tileView3);
        BOOST_CHECK_EQUAL(tile.observers.size(), 3);
        tile.removeObserver(&tileView3);
        BOOST_CHECK_EQUAL(tile.observers.size(), 2);
    }
}