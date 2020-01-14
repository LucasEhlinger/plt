#include "AI_Guard.h"
#include "Random.h"

using namespace ai;

state::Coordinate AI_Guard::action(state::Board &board) {
    if (board.playingPawn().on_duty) {
        if (board.playingPawn().getAP() > 0) {
            board.playingPawn().setAP(1);
            board.playingPawn().notify();
        }
        for (state::Pawn pawn : board.pawns)
            if (pawn.trespassing)
                return pawn.getCoordinate();
            auto pute = board.matrixAv_Tile(board.playingPawn());
        return ai::Random::action(pute);
    } else {
        std::vector<state::Coordinate> banes_coord;
        for (state::Pawn pawns : board.pawns)
            if (pawns.number_type == 6)
                banes_coord.emplace_back(pawns.getCoordinate());
        if (banes_coord.size() != 0) {
            int distance_min = 13;
            state::Coordinate closest_bane{0, 0};
            for (state::Coordinate bane : banes_coord) {
                int distance_bane = board.playingPawn().getCoordinate().distance(bane);
                if (distance_min > distance_bane) {
                    distance_min = distance_bane;
                    closest_bane = bane;
                }
                if (distance_min <= 2)
                    return closest_bane;
            }
            return closest_bane;
        }
        return ai::Random::action(board.matrixAv_Tile(board.playingPawn()));
    }
}
