#include "PawnView.h"

using namespace render;

PawnView::PawnView(state::Pawn pawn) : pawn(pawn) {}

void PawnView::update(state::IObservable* obj) {
    this->pawn = *static_cast<state::Pawn*>(obj);
}