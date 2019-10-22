#include "PawnVue.h"

using namespace render;

PawnVue::PawnVue(state::Pawn &pawn) : pawn(pawn) {}

void PawnVue::update() {
    this->pawn.getAP();
}