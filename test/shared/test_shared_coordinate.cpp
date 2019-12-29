
#include <boost/test/unit_test.hpp>
#include "state.h"
#include <stdexcept>      // std::out_of_range


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestSetup) {
    {
        Coordinate coo{11, 12};
        BOOST_CHECK_EQUAL(coo.getRow(), 11);
        BOOST_CHECK_EQUAL(coo.getColumn(), 12);
        coo.setRow(7);
        coo.setColumn(9);
        BOOST_CHECK_EQUAL(coo.getRow(), 7);
        BOOST_CHECK_EQUAL(coo.getColumn(), 9);

    }
    {
        Coordinate coo{11, 12};
        coo.setCoord(2, 8);
        BOOST_CHECK_EQUAL(coo.getRow(), 2);
        BOOST_CHECK_EQUAL(coo.getColumn(), 8);

    }
    {
        Coordinate coo{120};
        BOOST_CHECK(coo == Coordinate(9,3));
    }
}

BOOST_AUTO_TEST_CASE(TestConversion) {
    {
        Coordinate coo{12, 12};
        coo.setCoord(0);
        BOOST_CHECK_EQUAL(coo.getColumn(), 0);
        BOOST_CHECK_EQUAL(coo.getRow(), 0);
    }
    {
        Coordinate coo{0, 0};
        coo.setCoord(10);
        BOOST_CHECK_EQUAL(coo.getColumn(), 10);
        BOOST_CHECK_EQUAL(coo.getRow(), 0);
    }
    {
        Coordinate coo{0, 0};
        coo.setCoord(50);
        BOOST_CHECK_EQUAL(coo.getColumn(), 11);
        BOOST_CHECK_EQUAL(coo.getRow(), 3);
    }
    {
        Coordinate coo{0, 0};
        coo.setCoord(168);
        BOOST_CHECK_EQUAL(coo.getColumn(), 12);
        BOOST_CHECK_EQUAL(coo.getRow(), 12);
    }
    {
        Coordinate coo{3, 11};
        BOOST_CHECK_EQUAL(coo.getCoordInLine(), 50);
    }
    {
        Coordinate coo{0, 10};
        BOOST_CHECK_EQUAL(coo.getCoordInLine(), 10);
    }
    {
        Coordinate coo{0, 0};
        BOOST_CHECK_EQUAL(coo.getCoordInLine(), 0);
    }
}

BOOST_AUTO_TEST_CASE(testAnormalValue) {
    {
        Coordinate coo{0, 0};
        BOOST_CHECK_THROW(coo.setCoord(190), std::out_of_range);
    }
    {
        Coordinate coo{0, 0};
        BOOST_CHECK_THROW(coo.setCoord(13, 13), std::out_of_range);
    }
    {
        Coordinate coo{0, 0};
        BOOST_CHECK_THROW(coo.setCoord(145, 147), std::out_of_range);
    }
    {
        BOOST_CHECK_THROW(Coordinate(13, 13), std::out_of_range);
    }
    {
        BOOST_CHECK_THROW(Coordinate(169), std::out_of_range);
    }
}

BOOST_AUTO_TEST_CASE(testCubicTransformation) {
    {
        Coordinate coo{4, 7};
        auto x = coo.evenr_to_cube();
        BOOST_CHECK_EQUAL(x[0],5);
        BOOST_CHECK_EQUAL(x[1],-9);
        BOOST_CHECK_EQUAL(x[2],4);
    }

}