#include "TileView.h"

using namespace render;

TileView::TileView(state::Tile &tile) : tile(tile) {}

void TileView::update(state::IObservable*  obj) {
    this->tile = *static_cast<state::Tile*>(obj);
}