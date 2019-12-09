#include "Random.h"
#include <array>
#include <cmath>


using namespace ai;

state::Coordinate Random::action(std::vector<state::Coordinate> av_moves) {
    srand(time(NULL));
    return av_moves[rand() % av_moves.size()];
}