#include "Board.h"

using namespace ::state;

Board::Board() {
    day = true;
    //TODO : projet
}

void Board::changeTime() {
    day = !day;
}

void Board::addT(state::Tile tile) {
    tiles.push_back(tile);
}

//TODO : Board::addP