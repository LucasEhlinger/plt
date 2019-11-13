
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include <state/Start.h>
#include <state/Field.h>
#include "../../src/client/render/Scene.h"

BOOST_AUTO_TEST_CASE(TestSceneValues) {
    state::Start st{};
    state::Field fi{};
    state::Board board{};
    board.generate();

    render::Scene scene{board};
    auto tiles = scene.draw();

    BOOST_CHECK_EQUAL(tiles[6], st.number_type);
    BOOST_CHECK_EQUAL(tiles[7], fi.number_type);
    BOOST_CHECK_EQUAL(tiles[18], fi.number_type);
    BOOST_CHECK_EQUAL(tiles[19], fi.number_type);
}