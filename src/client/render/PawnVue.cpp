#include "PawnVue.h"

using namespace render;

PawnVue::PawnVue(state::Pawn &pawn) : pawn(&pawn) {}

void PawnVue::update(state::IObservable*  obj) {
    this->pawn = static_cast<state::Pawn*>(obj);
}