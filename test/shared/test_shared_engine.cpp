#include <boost/test/unit_test.hpp>
#include "state.h"
#include "engine.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestEngineGenerate) {
    {
        Board bo{};
        bo.generate();
        engine::Engine en{bo};
    }
}