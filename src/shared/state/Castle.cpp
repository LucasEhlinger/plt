#include "Castle.h"

using namespace ::state;

Castle::Castle() : Tile() {
    this->path = "./../../../res/hexagon-pack/PNG/castle.png";
}

/**
 * Apply effects of the Castle on the pawn
 * @param pawn Pawn affected pawn
 */
void Castle::effect(Pawn &pawn) {
    pawn.setAP(0);
}