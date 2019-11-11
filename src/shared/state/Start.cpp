#include "Start.h"

using namespace ::state;

Start::Start() : Tile() {
    moveCost = -100;
    number_type = 7;
}

void Start::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}
