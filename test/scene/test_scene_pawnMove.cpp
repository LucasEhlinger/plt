#include <boost/test/unit_test.hpp>
#include "state.h"
#include "engine.h"
#include "../client/render.h"

using namespace ::state;
using namespace ::engine;
using namespace ::render;

BOOST_AUTO_TEST_CASE(TestMove) {
    {
        state::Board board{};
        board.generate();
        render::Scene scene{board};
        engine::Engine engine1{board};
        engine1.move(engine1.board->pawns[0], state::Coordinate{0, 7});
        BOOST_CHECK(engine1.board->pawns[0].getCoordinate() == state::Coordinate(0, 7));
    }
}
BOOST_AUTO_TEST_CASE(WhoIsPlaying) {
    {
        state::Board board{};
        board.generate();
        render::Scene scene{board};
        engine::Engine engine1{board};
        BOOST_CHECK(engine1.playingPawn() == engine1.board->pawns[0]);
        BOOST_CHECK(engine1.board->pawns[0].isPlaying);
        engine1.nextTurn();
        BOOST_CHECK(engine1.board->pawns[1].isPlaying);
    }
}