#include <boost/test/unit_test.hpp>
#include "state.h"
#include "engine.h"


using namespace ::state;
using namespace ::engine;
BOOST_AUTO_TEST_CASE(TestGeneration){
    {
        Board bo{};
        bo.generate();
        bo.pawns.push_back(Player{Coordinate{0,6}, "player1", true});
        Engine en{bo};
        auto coo = en.matrixAv_Tile(en.board->pawns[0]);

        //TODO : Add a real test here.
    }
}