#include "StoneAge.h"
using namespace ::state;

void StoneAge::Effect(state::Pawn pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(+1);
}