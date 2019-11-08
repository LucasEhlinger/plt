#include "BoardView.h"

using namespace render;

BoardView::BoardView(state::Board &board) : board(board) {}

void BoardView::update(state::IObservable* obj) {
    this->board = *static_cast<state::Board*>(obj);
}