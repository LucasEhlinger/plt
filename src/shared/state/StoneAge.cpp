#include "StoneAge.h"

using namespace ::state;

StoneAge::StoneAge() : Tile() {
    number_type = 4;
}

void StoneAge::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(+1);
}
