#include "Engine.h"
#include "state.h"
using namespace engine;

Engine::Engine(state::Board& board) : board(&board){
    state::Player player1{state::Coordinate{0,6}, "player 1"};
    player1.number_type = 1;

    state::Player player2{state::Coordinate{12,6}, "player 2"};
    player2.number_type = 2;

    state::King king{state::Coordinate{6,6}};
    this->board->pawns.emplace_back(king);
    this->board->pawns.emplace_back(player1);
    this->board->pawns.emplace_back(player2);
}

void Engine::move(state::Pawn &pawn, state::Coordinate to){
    int position = to.getCoordInLine();
    if ( board->tiles.at(position).exist || (pawn.getAP() + board->tiles.at(position).getMoveCost()) >= 0){
        pawn.move(to);
        board->tiles.at(position).effect(pawn);
        pawn.notify();
    }
}