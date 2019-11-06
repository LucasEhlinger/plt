#include <boost/test/unit_test.hpp>
#include "state.h"
#include <fstream>
#include <sstream>
#include <string>


using namespace ::state;

BOOST_AUTO_TEST_CASE(TestGeneration) {
    {
        std::string filename = "./testing.txt";
        Board::generateFile(Board::generate(), filename);
        std::ifstream infile(filename);

        std::string line;
        for(int i = 0; i < 5; i++)
        {
            std::getline(infile, line);
            std::istringstream iss(line);
            std::string a;
            iss >> a;
            BOOST_CHECK_EQUAL(a, "Nu");

        }
    }
}