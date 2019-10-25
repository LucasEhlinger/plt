#include <boost/test/unit_test.hpp>
#include "state.h"
#include "../../src/client/render.h"

using namespace ::state;
using namespace ::render;

BOOST_AUTO_TEST_CASE(TestPawnObservable) {
    {
        Pawn pawn{Coordinate{12, 24}};
        PawnVue pawnVue{pawn};
        pawn.add(pawnVue);
        BOOST_CHECK_EQUAL(pawnVue.pawn->getAP(),0);

        pawn.setAP(12);
        pawn.notify();

        BOOST_CHECK_EQUAL(pawnVue.pawn->getAP(),12);
    }
    {
        Board bo{};
        BoardVue boardVue{bo};
        bo.add(boardVue);
        BOOST_CHECK(boardVue.board->day);
        bo.changeTime();
        bo.notify();
        BOOST_CHECK(!boardVue.board->day);
    }
    {
        Tile tile{Coordinate{16,64}};
        TileVue tileVue{tile};
        tile.add(tileVue);
    }

}