#include "StoneAge.h"
using namespace ::state;

StoneAge::StoneAge(state::Coordinate coordinate) : Tile(coordinate){
    this->path = "./../../../res/hexagon-pack/PNG/stonage.png";
}

void StoneAge::Effect(state::Pawn& pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(+1);
}
