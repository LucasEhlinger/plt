#include "AI_Guard.h"
#include "ai.h"

using namespace ai;

state::Coordinate AI_Guard::action(state::Board& board) {
    std::vector<state::Coordinate> banes_coord;
    for (state::Pawn pawns : board.pawns)
        if (pawns.number_type == 6)
            banes_coord.emplace_back(pawns.getCoordinate());
    if (banes_coord.size() != 0) {
        int distance_min = 13;
        state::Coordinate closest_bane{0,0};
        for (state::Coordinate bane : banes_coord) {
            int distance_bane = board.playingPawn().getCoordinate().distance(bane);
            if (distance_min > distance_bane) {
                distance_min = distance_bane;
                closest_bane = bane;
            }
            if (distance_min >= 2)
                return closest_bane;
        }
        board.playingPawn().setAP(1);
        return closest_bane;
    }
    board.playingPawn().setAP(1);
    return ai::Random::action(board.matrixAv_Tile(board.playingPawn()));
}
