#include <boost/test/unit_test.hpp>
#include "state.h"

using namespace ::state;

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
        BOOST_CHECK (co.property->getCoordinate() == pa.getCoordinate());
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
        BOOST_CHECK(ti.getCoordinate() == coo);
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

BOOST_AUTO_TEST_CASE(TestForest) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Forest forest{Coordinate{1, 2}};
        pawn.setAP(10);
        forest.Effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
        //TODO : Check if the path file exist
        //boost::filesystem::path pathObj(forest.path);
        //BOOST_CHECK(boost::filesystem::exists(pathObj));
    }
}
BOOST_AUTO_TEST_CASE(TestStoneAge) {
    {
        Pawn pawn{Coordinate{2, 1}};
        StoneAge sta{Coordinate{1, 2}};
        pawn.setAP(10);
        sta.Effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
    }
}

BOOST_AUTO_TEST_CASE(TestSwamp) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Swamp swp{Coordinate{1, 2}};
        pawn.setAP(10);
        pawn.setLP(4);
        swp.Effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
        BOOST_CHECK_EQUAL(pawn.getLP(), 3);
    }
}