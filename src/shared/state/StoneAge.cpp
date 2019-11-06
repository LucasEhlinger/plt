#include "StoneAge.h"
using namespace ::state;

StoneAge::StoneAge() : Tile(){
    this->path = "./../../../res/hexagon-pack/PNG/stonage.png";
}

void StoneAge::effect(state::Pawn& pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(+1);
}
