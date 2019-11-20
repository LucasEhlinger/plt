#include "Engine.h"
#include "state.h"

#define HEIGHT  13
#define WIDTH   13

using namespace engine;

Engine::Engine(state::Board& board) : board(&board){
    state::Player player1{state::Coordinate{0,6}, "player 1", true};
    player1.number_type = 1;

    state::Player player2{state::Coordinate{12,6}, "player 2", false};
    player2.number_type = 2;

    state::King king{state::Coordinate{6,6}};
    this->board->pawns.emplace_back(king);
    this->board->pawns.emplace_back(player1);
    this->board->pawns.emplace_back(player2);
}

void Engine::move(state::Pawn &pawn, state::Coordinate to){
    int position = to.getCoordInLine();
    if ( board->tiles.at(position).exist && (pawn.getAP() + board->tiles.at(position).getMoveCost()) >= 0){
        pawn.move(to);
        board->tiles.at(position).effect(pawn);
        pawn.notify();
    }
}

std::array<int, 169> Engine::matrixAv_Tile(state::Pawn &pawn) {
    std::array<int, 169> table;
    table.fill(9);

    int x = pawn.getCoordinate().getRow();
    int y = pawn.getCoordinate().getColumn();
    int ap = pawn.getAP();

    if (x - 1 >= 0)
        if (ap + board->tiles.at((x - 1) * HEIGHT + y).getMoveCost() >= 0)
            table.at((x - 1) * HEIGHT + y) = 0;
    if (x + 1 < HEIGHT)
        if (ap + board->tiles.at((x + 1) * HEIGHT + y).getMoveCost() >= 0)
            table.at((x + 1) * HEIGHT + y) = 0;
    if (y - 1 >= 0)
        if (ap + board->tiles.at(x * HEIGHT + (y - 1)).getMoveCost() >= 0)
            table.at(x * HEIGHT + (y - 1)) = 0;
    if (y + 1 < WIDTH)
        if (ap + board->tiles.at(x * HEIGHT + (y + 1)).getMoveCost() >= 0)
            table.at(x * HEIGHT + (y + 1)) = 0;
    if (y + 1 < WIDTH && x - 1 >= 0)
        if (ap + board->tiles.at((x - 1) * HEIGHT + (y + 1)).getMoveCost() >= 0)
            table.at((x - 1) * HEIGHT + (y + 1)) = 0;
    if (y - 1 >= 0 && x + 1 < HEIGHT)
        if (ap + board->tiles.at((x + 1) * HEIGHT + (y - 1)).getMoveCost() >= 0)
            table.at((x + 1) * HEIGHT + (y - 1)) = 0;
    return table;
}
