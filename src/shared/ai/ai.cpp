#include "ai.h"

using namespace ai;

state::Coordinate Ai::AI_rand(std::vector<state::Coordinate> av_moves) {
    return av_moves[rand() % av_moves.size()];
}