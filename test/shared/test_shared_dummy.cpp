
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

BOOST_AUTO_TEST_CASE(TestBoard) {
    {
        Board bo{};
        BOOST_CHECK(bo.day);
        bo.changeTime();
        BOOST_CHECK_EQUAL(bo.day, false);
    }
    {
        Board bo{};
        Pawn pa = Pawn(Coordinate{12, 21});
        bo.addPawn(pa);
        BOOST_CHECK_EQUAL(bo.pawns.front().getCoordinate().getRow(),pa.getCoordinate().getRow());
        BOOST_CHECK_EQUAL(bo.pawns.front().getCoordinate().getColumn(),pa.getCoordinate().getColumn());
    }
}

BOOST_AUTO_TEST_CASE(TestCastle) {
    {
        Castle ca = Castle{Coordinate(12, 21)};
        Pawn pa = Pawn(Coordinate{12, 21});
        pa.setAP(11);
        ca.Effect(pa);
        BOOST_CHECK_EQUAL(pa.getAP(), 0);
    }
}

BOOST_AUTO_TEST_CASE(TestColony) {
    {
        Colony co = Colony{Coordinate(12, 21)};
        Pawn pa = Pawn(Coordinate{12, 21});
        co.Effect(pa);
        BOOST_CHECK_EQUAL(co.property->getCoordinate().getRow(), pa.getCoordinate().getRow());
        BOOST_CHECK_EQUAL(co.property->getCoordinate().getColumn(), pa.getCoordinate().getColumn());

    }
}

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

BOOST_AUTO_TEST_CASE(TestMountain) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Mountain *mount = new Mountain(Coordinate{1, 2});
        pawn.setAP(3);
        mount->Effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 1);

    }
}

BOOST_AUTO_TEST_CASE(TestStart) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Start start{Coordinate{1, 2}};
        pawn.setAP(10);
        start.Effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), -90);

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

BOOST_AUTO_TEST_CASE(TestRuin) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Ruin *ruin = new Ruin(Coordinate{1, 2});
        pawn.setAP(10);
        ruin->Effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
    }
}

BOOST_AUTO_TEST_CASE(TestField) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Field *field = new Field(Coordinate{1, 2});
        pawn.setAP(10);
        field->Effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
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