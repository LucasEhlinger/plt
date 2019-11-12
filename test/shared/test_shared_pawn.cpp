
#include <boost/test/unit_test.hpp>
#include "state.h"
#include <stdexcept>      // std::out_of_range


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestBane) {
    {
        Bane ba{Coordinate{12, 4}, "bane"};
        BOOST_CHECK_EQUAL(ba.getCoordinate().getRow(), 12);
        BOOST_CHECK_EQUAL(ba.getCoordinate().getColumn(), 4);
    }
}

BOOST_AUTO_TEST_CASE(TestKing) {
    {
        King king{Coordinate{12, 12}};

        BOOST_CHECK_EQUAL(king.name, "King");

        BOOST_CHECK_EQUAL(king.getRot(), 0);
        king.modifyRot();
        BOOST_CHECK_EQUAL(king.getRot(), -1);
    }
}

BOOST_AUTO_TEST_CASE(TestPlayer) {
    {
        Player player1{Coordinate{12, 11}, "me"};
        Player player2{Coordinate{12, 11}, "me"};
        BOOST_CHECK(player1 == player2);
    }
}

BOOST_AUTO_TEST_CASE(TestGuard) {
    {
        Guard guard{Coordinate{12, 11}, "guard"};
        BOOST_CHECK_EQUAL(guard.name, "guard");
    }
}

BOOST_AUTO_TEST_CASE(TestMove) {
    {
        Player player{Coordinate{12, 11}, "me"};
        player.move(Coordinate{3, 6});
        BOOST_CHECK(player.getCoordinate() == Coordinate(3, 6));
    }
    {
        Player player{Coordinate{12, 11}, "me"};
        BOOST_CHECK_THROW(player.move(Coordinate(13, 189)),std::out_of_range);
    }
}

