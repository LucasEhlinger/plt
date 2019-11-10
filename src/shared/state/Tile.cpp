#include "Tile.h"

using namespace ::state;

Tile::Tile() {}

/**
 * Apply effects of the tile on the pawn
 * @param pawn Pawn affected pawn
 */
void Tile::effect(state::Pawn &pawn) {
    pawn.modifyAP(this->moveCost);
}

int Tile::getMoveCost() const {
    return this->moveCost;
}

bool Tile::operator==(state::Tile &rhs) {
    return rhs.moveCost == moveCost &&
           rhs.observers.size() == observers.size();
}