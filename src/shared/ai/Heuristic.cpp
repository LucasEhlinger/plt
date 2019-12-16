#include "Heuristic.h"
#include "Random.h"

using namespace ai;

state::Coordinate Heuristic::action(state::Board &board) {
    state::Pawn playing = board.playingPawn();
    state::Coordinate current_coord = playing.getCoordinate();
    bool kill_king, kill_king_q, kill_prestige, kill_prestige_q = false;

    kill_king = sim_attack(playing, state::Coordinate{6, 6}, 0);
    kill_king_q = sim_attack(playing, state::Coordinate{6, 6}, 0);

    bool prestige_win = false;
    state::Coordinate goal{0, 0};
    for (int i = 0; i < board.pawns.size(); ++i)
        if (board.pawns.at(i).getResources().prestige - playing.getResources().prestige < 2 &&
            playing.getResources().prestige < board.pawns.at(i).getResources().prestige) {
            prestige_win = true;
            goal = board.pawns.at(i).getCoordinate();
        }
    if (prestige_win) {
        kill_prestige = sim_attack(playing, goal, 0);
        kill_prestige_q = sim_attack(playing, goal, 0);
    }

    if (kill_king)
        return state::Coordinate{6, 6};
    else if (kill_king_q || kill_prestige_q)
        return ai::Random::action(board.matrixAv_Tile(playing));
    else if (kill_prestige)
        return goal;
    else
        return ai::Random::action(board.matrixAv_Tile(playing));
}

bool Heuristic::sim_attack(state::Pawn playing, state::Coordinate goal, int modifier) {
    int ratio = 0;
    playing.modifyStats(modifier, 0, 0, 0);
    for (int i = 100; --i;) {
        playing.move(goal);
        if (playing.getCoordinate() == goal)
            ++ratio;
    }
    if (ratio > 70)
        return true;
    return false;
}