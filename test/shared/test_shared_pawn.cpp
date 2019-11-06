
#include <boost/test/unit_test.hpp>
#include "state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestBane) {
    {
        Bane ba{Coordinate{12, 21}};
        BOOST_CHECK_EQUAL(ba.getCoordinate().getRow(), 12);
        BOOST_CHECK_EQUAL(ba.getCoordinate().getColumn(), 21);

    }
}

BOOST_AUTO_TEST_CASE(TestKing) {
    {
        King king{Coordinate{12, 12}};
        BOOST_CHECK_EQUAL(king.getRot(), 0);
        king.modifyRot();
        BOOST_CHECK_EQUAL(king.getRot(), -1);
    }
}

BOOST_AUTO_TEST_CASE(TestPlayer) {
    {
        Player player{Coordinate{12, 11}};
    }
}

