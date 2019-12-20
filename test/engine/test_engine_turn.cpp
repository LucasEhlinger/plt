#include <boost/test/unit_test.hpp>
#include "state.h"
#include "engine.h"


using namespace ::state;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestTurns) {
    Board bo{};
    bo.generate();
    Engine en{bo};

    for (int i = 0; i < 20; i++) {
        en.nextTurn();
        en.playingPawn().setAP(3);
        en.playingPawn().setLP(3);
        en.pathfinding(Coordinate{9,7});
    }

}
