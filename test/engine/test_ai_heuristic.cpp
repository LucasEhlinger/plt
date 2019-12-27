#include <boost/test/unit_test.hpp>
#include "state.h"
#include "engine.h"
#include "ai.h"


using namespace ::state;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestHeuristicAi) {
    Board bo{};
    bo.generate();
    Engine en{bo};
    //ai::Heuristic ai;

    /*for(int i= 0; i <200; i++) {
        BOOST_CHECK_NO_THROW(en.move(en.playingPawn(), ai.action(bo)));
        en.nextTurn();
    }*/
}