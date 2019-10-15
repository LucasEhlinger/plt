#include "Colony.h"
using namespace ::state;

/**
 * Apply effects of the Colony on the pawn
 * @param pawn Pawn affected pawn
 */
void Colony::Effect(Pawn& pawn) {
    pawn.modifyAP(moveCost);
    this->property = pawn;
}