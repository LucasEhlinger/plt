#include "StoneAge.h"
using namespace ::state;

StoneAge::StoneAge() : Tile(){
}

void StoneAge::effect(state::Pawn& pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(+1);
}
