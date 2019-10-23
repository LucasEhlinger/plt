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
        pawn.add(pawnVue);
        pawn.setAP(12);
        pawn.notify();

        Tile ti1{Coordinate{12, 24}};
        TileVue tileVue{ti1};
        ti1.add(tileVue);

        BOOST_CHECK_EQUAL(pawn.observers.size(), 2);
        BOOST_CHECK_EQUAL(ti1.observers.size(), 1);

    }

}