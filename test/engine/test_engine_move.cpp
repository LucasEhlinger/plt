#include <boost/test/unit_test.hpp>
#include "state.h"
#include "engine.h"


using namespace ::state;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestMove){
    {
        Board bo{};
        bo.generate();

        Engine en{bo};

    }
}