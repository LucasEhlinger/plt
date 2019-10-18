#include "Start.h"
#include <iostream>
using namespace ::state;

Start::Start(Coordinate position):Tile(position) {
    this->path = "./../../../res/hexagon-pack/PNG/start.png"
}

void Start::Effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}
