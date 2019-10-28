#include <boost/test/unit_test.hpp>
#include "state.h"
#include "../../src/client/render.h"

using namespace ::state;
using namespace ::render;

BOOST_AUTO_TEST_CASE(TestPawnObservable) {
    {
        Pawn pawn{Coordinate{12, 24}};
        PawnVue pawnVue{pawn};
        pawn.addObserver(&pawnVue);
        BOOST_CHECK_EQUAL(pawnVue.pawn.getAP(),0);

        pawn.setAP(12);
        BOOST_CHECK_EQUAL(pawnVue.pawn.getAP(),0);
        pawn.notify();

        BOOST_CHECK_EQUAL(pawnVue.pawn.getAP(),12);
    }
}
BOOST_AUTO_TEST_CASE(TestBoardObservable){
    {
        Board bo{};
        BoardVue boardVue{bo};
        bo.addObserver(&boardVue);
        BOOST_CHECK(boardVue.board.day);
        bo.changeTime();
        bo.notify();
        BOOST_CHECK(!boardVue.board.day);
    }
}
BOOST_AUTO_TEST_CASE(TestTileObservable){
    {
        Tile tile{Coordinate{16,64}};
        TileVue tileVue{tile};
        tile.addObserver(&tileVue);
    }
}