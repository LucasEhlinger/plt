#include "Swamp.h"

using namespace ::state;

Swamp::Swamp() : Tile() {
}

void Swamp::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(-1);
}
