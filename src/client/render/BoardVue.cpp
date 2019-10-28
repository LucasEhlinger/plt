#include "BoardVue.h"

using namespace render;

BoardVue::BoardVue(state::Board &board) : board(board) {}

void BoardVue::update(state::IObservable* obj) {
    this->board = *static_cast<state::Board*>(obj);
}

void BoardVue::testeur() {
    printf("BoardVue");
}