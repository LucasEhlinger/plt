#include "Swamp.h"

using namespace ::state;

Swamp::Swamp() : Tile() {
    number_type = 5;
    exist = true;
}

void Swamp::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(-1);
}
