#include "Ai.h"
#include <cmath>


using namespace ai;

state::Coordinate Ai::AI_rand(std::vector<state::Coordinate> av_moves) {
    srand(time(NULL));
    return av_moves[rand() % av_moves.size()];
}