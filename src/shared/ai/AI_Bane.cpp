#include "AI_Bane.h"

using namespace ai;

state::Coordinate AI_Bane::action(state::Board &board) {
    for (state::Pawn pawn : board.pawns)
        if (board.playingPawn().getCoordinate().distance(pawn.getCoordinate()) == 1 &&
            board.tiles.at(pawn.getCoordinate().getCoordInLine()).number_type != 8 &&
            board.tiles.at(pawn.getCoordinate().getCoordInLine()).number_type != 4)
            return pawn.getCoordinate();

    std::vector<state::Coordinate> colonies;
    for (int i = 0; i < board.tiles.size(); ++i)
        if (board.tiles.at(i).number_type == 6)
            colonies.emplace_back(state::Coordinate{i});

    state::Coordinate closest_colony{colonies.back()};
    int min_distance = 13;
    for (state::Coordinate colony : colonies) {
        int cur_distance = board.playingPawn().getCoordinate().distance(colony);
        if (cur_distance < min_distance &&
            colony.getCoordInLine() != board.playingPawn().getCoordinate().getCoordInLine()) {
            closest_colony = colony;
            min_distance = cur_distance;
        }
    }
    return closest_colony;
}
