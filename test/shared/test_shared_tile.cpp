#include <boost/test/unit_test.hpp>
#include "state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestCastle) {
    {
        Castle ca = Castle{};
        Pawn pa = Pawn(Coordinate{12, 21});
        pa.setAP(11);
        ca.effect(pa);
        BOOST_CHECK_EQUAL(pa.getAP(), 0);
    }
    {
        Castle ca1 = Castle{};
        Castle ca2 = Castle{};
        BOOST_CHECK(ca1 == ca2);
    }
}

BOOST_AUTO_TEST_CASE(TestColony) {
    {
        Colony co = Colony{};
        Pawn pa = Pawn(Coordinate{12, 21});
        co.effect(pa);
        BOOST_CHECK (co.property == &pa);
    }
}

BOOST_AUTO_TEST_CASE(TestMountain) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Mountain mount{};
        pawn.setAP(3);
        mount.effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 1);
        BOOST_CHECK_EQUAL(mount.getMoveCost(), -2);

    }
}

BOOST_AUTO_TEST_CASE(TestStart) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Start start{};
        pawn.setAP(10);
        start.effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), -90);
        BOOST_CHECK_EQUAL(start.getMoveCost(), -100);

    }
}

BOOST_AUTO_TEST_CASE(TestRuin) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Ruin ruin{};
        pawn.setAP(10);
        ruin.effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
        BOOST_CHECK_EQUAL(ruin.getMoveCost(), -1);
    }
}

BOOST_AUTO_TEST_CASE(TestField) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Field field{};
        pawn.setAP(10);
        field.effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
    }
}

BOOST_AUTO_TEST_CASE(TestForest) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Forest forest{};
        pawn.setAP(10);
        forest.effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
        //TODO : Check if the path file exist
        //boost::filesystem::path pathObj(forest.path);
        //BOOST_CHECK(boost::filesystem::exists(pathObj));
    }
}
BOOST_AUTO_TEST_CASE(TestStoneAge) {
    {
        Pawn pawn{Coordinate{2, 1}};
        StoneAge sta{};
        pawn.setAP(10);
        sta.effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
    }
}

BOOST_AUTO_TEST_CASE(TestSwamp) {
    {
        Pawn pawn{Coordinate{2, 1}};
        Swamp swp{};
        pawn.setAP(10);
        pawn.setLP(4);
        swp.effect(pawn);
        BOOST_CHECK_EQUAL(pawn.getAP(), 9);
        BOOST_CHECK_EQUAL(pawn.getLP(), 3);
    }
}