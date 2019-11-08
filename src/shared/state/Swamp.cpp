#include "Swamp.h"

using namespace ::state;

Swamp::Swamp() : Tile() {
    this->path = "Sw";
}

void Swamp::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(-1);
}
