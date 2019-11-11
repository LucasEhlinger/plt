#include "Colony.h"

using namespace ::state;

Colony::Colony() : Tile() {
    this->property = nullptr;
    number_type = 6;
}

/**
 * Apply effects of the Colony on the pawn
 * @param pawn Pawn affected pawn
 */
void Colony::effect(Pawn &pawn) {
    pawn.modifyAP(moveCost);
    this->property = &pawn;
}