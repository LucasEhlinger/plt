#include "Tile.h"

using namespace ::state;

Tile::Tile(Coordinate position):coordinate(position) {}
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
void Tile::Effect(state::Pawn& pawn){
    pawn.modifyAP(this->moveCost);
}

void Tile::notify() {
    for(auto obs = observers.begin(); obs != observers.end(); ++obs){
        obs.base()->update(this);
    }
}

void Tile::add(state::IObserver observer) {
    observers.push_back(observer);
}

void Tile::remove(state::IObserver observer) {
    //remove observer from list.
}