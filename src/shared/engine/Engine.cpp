#include "Engine.h"

using namespace engine;

Engine::Engine(state::Board& board) : board(board){}

void Engine::move(state::Pawn &pawn, state::Coordinate to){
    int position = to.getCoordInLine();
    if (board.tiles.at(position) != NULL)
    {
        pawn.move(to);
    }
}