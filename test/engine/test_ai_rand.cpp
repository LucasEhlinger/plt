#include <boost/test/unit_test.hpp>
#include "state.h"
#include "engine.h"
#include "ai.h"


using namespace ::state;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestRandomAi) {
    Board bo{};
    bo.generate();
    Engine en{bo};
    ai::Random ai;

    std::vector<state::Coordinate> av_moves = en.matrixAv_Tile(en.playingPawn());
    std::array<int, 169> av_tiles;
    av_tiles.fill(9);

    for (int j = 0; j < av_moves.size(); ++j)
        av_tiles.at(av_moves.at(j).getCoordInLine()) = 0;

    /*for(int i= 0; i <200; i++) {
        en.playingPawn().setAP(3);
        en.playingPawn().setLP(3);
        //BOOST_CHECK_THROW(en.move(en.playingPawn(), ai.action(av_moves)), EXC_ARITHMETIC);
        //BOOST_CHECK_NO_THROW(en.move(en.playingPawn(), ai.action(av_moves)));
        en.nextTurn();
    }*/

}
