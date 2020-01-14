#include "Colony.h"

using namespace ::state;

Colony::Colony() : Tile() {
    property = nullptr;
    number_type = 6;
    exist = true;
}

/**
 * Apply effects of the Colony on the pawn
 * @param pawn Pawn affected pawn
 */
void Colony::effect(Pawn &pawn) {
    pawn.modifyAP(moveCost);
    this->property = &pawn;
    if (property->number_type == 6)
        pawn.modifyResources(0,0,1,0);
}

Colony::~Colony() {
}