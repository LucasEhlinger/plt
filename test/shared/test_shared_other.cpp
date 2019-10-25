
#include <boost/test/unit_test.hpp>
#include "state.h"

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
    {
        Coordinate coo1{123, 987};
        Coordinate coo2{123, 987};
        Coordinate coo3{1098, 1};
        BOOST_CHECK(coo1 == coo2);
        BOOST_CHECK(!(coo1 == coo3));

    }
}

BOOST_AUTO_TEST_CASE(TestResources) {
    {
        Resources res{0, 0, 0, 0};
        res.modifyGold(+2);
        BOOST_CHECK_EQUAL(res.gold, 2);
    }
    {
        Resources res{0, 0, 0, 0};
        res.modifyMana(+2);
        BOOST_CHECK_EQUAL(res.mana, 2);
    }
    {
        Resources res{0, 0, 0, 0};
        res.modifyPrestige(+2);
        BOOST_CHECK_EQUAL(res.prestige, 2);
    }
    {
        Resources res{0, 0, 0, 0};
        res.modifyRot(+2);
        BOOST_CHECK_EQUAL(res.rot, 2);
    }
}

BOOST_AUTO_TEST_CASE(TestStats) {
    {
        Stats sta{0, 0, 0, 0};
        sta.setCombativeness(2);
        BOOST_CHECK_EQUAL(sta.getCombativeness(), 2);
    }
    {
        Stats sta{0, 0, 0, 0};
        sta.setPresenceOfMind(4);
        BOOST_CHECK_EQUAL(sta.getPresenceOfMind(), 4);
    }
    {
        Stats sta{0, 0, 0, 0};
        sta.setSpirituality(8);
        BOOST_CHECK_EQUAL(sta.getSpirituality(), 8);
    }
    {
        Stats sta{0, 0, 0, 0};
        sta.setVitality(16);
        BOOST_CHECK_EQUAL(sta.getVitality(), 16);
    }
}

BOOST_AUTO_TEST_CASE(TestBoard) {
    {
        Board bo{};
        BOOST_CHECK(bo.day);
        bo.changeTime();
        BOOST_CHECK(!bo.day);
    }
}