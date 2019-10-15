
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Board.h"
#include "../../src/shared/state/Coordinate.h"
#include "state/Tile.h"


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestCoordinate) {
    {
        Coordinate coo{123, 321};
        BOOST_CHECK_EQUAL(coo.getRow(), 123);
        BOOST_CHECK_EQUAL(coo.getColumn(), 321);
        coo.setRow(456);
        coo.setColumn(987);
        BOOST_CHECK_EQUAL(coo.getRow(), 456);
        BOOST_CHECK_EQUAL(coo.getColumn(), 987);

    }
    {
        Coordinate coo{123, 321};
        coo.setCoord(456, 987);
        BOOST_CHECK_EQUAL(coo.getRow(), 456);
        BOOST_CHECK_EQUAL(coo.getColumn(), 987);

    }
}

BOOST_AUTO_TEST_CASE(TestBoard) {
    {
        Board bo{};
        BOOST_CHECK(bo.day);
        bo.changeTime();
        BOOST_CHECK_EQUAL(bo.day, false);
    }
}