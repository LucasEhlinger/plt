#include "TileVue.h"

using namespace render;

TileVue::TileVue(state::Tile &tile) : tile(tile) {}

void TileVue::update(state::IObservable*  obj) {
    this->tile = *static_cast<state::Tile*>(obj);
}