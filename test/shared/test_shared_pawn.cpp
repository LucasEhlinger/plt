
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

        BOOST_CHECK_EQUAL(king.getRot(), 1);
        king.modifyRot();
        BOOST_CHECK_EQUAL(king.getRot(), 0);
    }
}

BOOST_AUTO_TEST_CASE(TestPlayer) {
    {
        Player player1{Coordinate{12, 11}, "me", false};
        Player player2{Coordinate{12, 11}, "me", false};
        BOOST_CHECK(player1 == player2);
    }
    {
        Player player1{Coordinate{12, 11}, "me", false};
        player1.set_number_type(3);
        BOOST_CHECK_EQUAL(player1.number_type, 3);
    }
}

BOOST_AUTO_TEST_CASE(TestGuard) {
    {
        Guard guard{Coordinate{12, 11}, "guard", false};
        BOOST_CHECK_EQUAL(guard.name, "guard");
    }
}

BOOST_AUTO_TEST_CASE(TestMove) {
    {
        Player player{Coordinate{12, 11}, "me", false};
        player.move(Coordinate{3, 6});
        BOOST_CHECK(player.getCoordinate() == Coordinate(3, 6));
    }
    {
        Player player{Coordinate{12, 11}, "me", false};
        BOOST_CHECK_THROW(player.move(Coordinate(13, 189)), std::out_of_range);
    }
}

BOOST_AUTO_TEST_CASE(TestAttack) {
    {
        Player player1{Coordinate{12, 11}, "test1", false};
        Player player2{Coordinate{12, 11}, "test2", false};
        player1.setResources(Resources{0,0,0,6});
        BOOST_CHECK_EQUAL(player1.getResources().rot, 6);
        player1.attack(player2, true, 0);
    }
    {
        Player player1{Coordinate{12, 11}, "test1", false};
        Player player2{Coordinate{12, 11}, "test2", false};
        player2.setResources(Resources{0,0,0,6});
        player1.attack(player2, true, 0);
    }
    {
        Player player1{Coordinate{12, 11}, "test1", false};
        Player player2{Coordinate{12, 11}, "test2", false};
        player1.setResources(Resources{0,0,0,6});
        player1.attack(player2, false, 0);
    }
}

BOOST_AUTO_TEST_CASE(TestModifyStats){
    {
        Player player1{Coordinate{12, 11}, "test1", false};
        player1.setStats(Stats{1,2,3,4});
        player1.modifyStats(4,-2,3,-1);
        BOOST_CHECK_EQUAL(player1.getCombativeness(), 5);
        BOOST_CHECK_EQUAL(player1.getVitality(), 0);
        BOOST_CHECK_EQUAL(player1.getPresenceOfMind(), 6);
        BOOST_CHECK_EQUAL(player1.getSpirituality(), 3);
    }
}