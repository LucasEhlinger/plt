#include "Ai.h"
#include <string>
#include <iostream>
#include <array>
#include <cmath>


using namespace ai;

state::Coordinate Ai::AI_rand(std::vector<state::Coordinate> av_moves) {
    srand(time(NULL));
    return av_moves[rand() % av_moves.size()];
}