
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