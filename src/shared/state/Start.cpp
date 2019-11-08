#include "Start.h"
#include <iostream>
using namespace ::state;

Start::Start():Tile() {
    this->path = "St";
    moveCost     = -100;
}

void Start::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}
