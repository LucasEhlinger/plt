
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Board.h"
#include "../../src/shared/state/Coordinate.h"
#include "../../src/shared/state/Tile.h"
#include "../../src/shared/state/Resources.h"
#include "../../src/shared/state/Start.h"

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


BOOST_AUTO_TEST_CASE(TestTile) {
    {
        Coordinate coo{1, 2};
        Tile ti{coo};
        BOOST_CHECK_EQUAL(ti.getCoordinate().getRow(), coo.getRow());
        BOOST_CHECK_EQUAL(ti.getCoordinate().getColumn(), coo.getColumn());
    }
}

BOOST_AUTO_TEST_CASE(TestResources) {
    {
        Resources res{};
        res.gold = 0;
        res.modifyGold(+2);
        BOOST_CHECK_EQUAL(res.gold, 2);
    }
    {
        Resources res{};
        res.mana = 0;
        res.modifyMana(+2);
        BOOST_CHECK_EQUAL(res.mana, 2);
    }
    {
        Resources res{};
        res.prestige = 0;
        res.modifyPrestige(+2);
        BOOST_CHECK_EQUAL(res.prestige, 2);
    }
    {
        Resources res{};
        res.rot = 0;
        res.modifyRot(+2);
        BOOST_CHECK_EQUAL(res.rot, 2);
    }
}

BOOST_AUTO_TEST_CASE(TestMoveCosts) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Start start{Coordinate{1, 2}};

        pawn.setAP(10);
        start.Effect(*pawn);

        BOOST_CHECK_EQUAL(pawn.getAP(), -90);
    }
}
