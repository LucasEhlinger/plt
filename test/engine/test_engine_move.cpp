#include <boost/test/unit_test.hpp>
#include "state.h"
#include "engine.h"


using namespace ::state;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestMove){
    {
        Board bo{};
        bo.generate();
        bo.pawns.push_back(Player{Coordinate{0,6}, "player1", true});
        Engine en{bo};
        en.move(Coordinate{1,7});

        BOOST_CHECK(bo.pawns.front().getCoordinate() == en.board->pawns.front().getCoordinate());
    }
}

BOOST_AUTO_TEST_CASE(TestAttack){
    {
        Board bo{};
        bo.generate();
        bo.pawns.push_back(Player{Coordinate{0,7}, "player2", true});
        Engine en{bo};
        en.move(Coordinate{0,7});
    }
}
