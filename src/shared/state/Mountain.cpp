#include "Mountain.h"

using namespace ::state;

Mountain::Mountain() : Tile() {
    moveCost = -2;
    number_type = 3;
    exist = true;
}

void Mountain::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}