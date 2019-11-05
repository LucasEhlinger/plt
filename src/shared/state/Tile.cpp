#include "Tile.h"

using namespace ::state;

Tile::Tile(Coordinate position) : coordinate(position) {}

/**
 * Get tile coordinates
 * @return Coordinate object containing x and y position
 */
Coordinate Tile::getCoordinate() {
    return this->coordinate;
}

/**
 * Apply effects of the tile on the pawn
 * @param pawn Pawn affected pawn
 */
void Tile::effect(state::Pawn &pawn) {
    pawn.modifyAP(this->moveCost);
}

void Tile::setCoordinate(const state::Coordinate &coordinate) {
    this->coordinate = coordinate;
}

int Tile::getMoveCost() const {
    return this->moveCost;
}

bool Tile::operator==(state::Tile &rhs) {
    return rhs.moveCost == moveCost &&
           rhs.coordinate == coordinate &&
           rhs.path == path &&
           rhs.observers.size() == observers.size();
}