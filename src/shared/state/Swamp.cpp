#include "Swamp.h"
using namespace ::state;

void Swamp::Effect(state::Pawn pawn) {
    pawn.modifyAP(moveCost);
    pawn.modifyLP(-1);
}