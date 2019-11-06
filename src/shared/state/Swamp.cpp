#include "Swamp.h"

using namespace ::state;

Swamp::Swamp() : Tile() {
    this->path = "./../../../res/hexagon-pack/PNG/swamp.png";
}

void Swamp::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(-1);
}
