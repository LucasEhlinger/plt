
#include <boost/test/unit_test.hpp>
#include "state.h"

using namespace ::state;

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
    {
        Resources res1{1,2,3,4};
        Resources res2{1,2,3,4};
        BOOST_CHECK(res1 == res2);
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
    {
        Stats sta1{1,2,3,4};
        Stats sta2{1,2,3,4};
        BOOST_CHECK(sta1 == sta2);
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