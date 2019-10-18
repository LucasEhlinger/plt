#include "Colony.h"
using namespace ::state;

Colony::Colony(state::Coordinate coordinate) :Tile(coordinate){
    this->property = nullptr;
    this->path = "./../../../res/hexagon-pack/PNG/colony.png"
}

/**
 * Apply effects of the Colony on the pawn
 * @param pawn Pawn affected pawn
 */
void Colony::Effect(Pawn& pawn) {
    pawn.modifyAP(moveCost);
    this->property = &pawn;
}