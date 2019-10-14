#include "Board.h"

using namespace ::state;

bool Board::isDay() {
    if ((this->time > this->sunrise) || (this->time < this->sunset)) {
        return true;
    }
    return false;
}

void Board::addT(state::Tile tile) {
    tiles.push_back(tile);
}

//TODO : Board::addP