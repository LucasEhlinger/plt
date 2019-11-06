#include "Start.h"
#include <iostream>
using namespace ::state;

Start::Start():Tile() {
    this->path = "./../../../res/hexagon-pack/PNG/start.png";
    moveCost     = -100;
}

void Start::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}
