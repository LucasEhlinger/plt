#include "Colony.h"
using namespace ::state;

void Colony::Effect(Pawn& pawn) {
    pawn.modifyAP(moveCost);
    this->property = pawn;
}