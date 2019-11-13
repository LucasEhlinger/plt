#include "Castle.h"

using namespace ::state;

Castle::Castle() : Tile() {
    number_type = 8;
    exist = true;
}

/**
 * Apply effects of the Castle on the pawn
 * @param pawn Pawn affected pawn
 */
void Castle::effect(Pawn &pawn) {
    pawn.setAP(0);
}