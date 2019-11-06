#include "Mountain.h"

using namespace ::state;

Mountain::Mountain() : Tile() {
    this->path = "./../../../res/hexagon-pack/PNG/mountain.png";
    moveCost = -2;
}

void Mountain::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}