#include "Colony.h"
using namespace ::state;

void Colony::Effect(state::Pawn pawn) {
    pawn.modifyAP(moveCost);
    this->property = pawn;
}