#include "Castle.h"
using namespace ::state;

void Castle::Effect(state::Pawn pawn) {
    pawn.setAP(0);
}