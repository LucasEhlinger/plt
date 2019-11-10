#include "Mountain.h"

using namespace ::state;

Mountain::Mountain() : Tile() {
    moveCost = -2;
}

void Mountain::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}