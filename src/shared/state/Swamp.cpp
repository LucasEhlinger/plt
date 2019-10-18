#include "Swamp.h"
using namespace ::state;

Swamp::Swamp(state::Coordinate coordinate) : Tile(coordinate){
    this->path = "./../../../res/hexagon-pack/PNG/swamp.png"
}

void Swamp::Effect(state::Pawn& pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(-1);
}
