#include "Mountain.h"
using namespace ::state;

Mountain::Mountain(state::Coordinate coordinate):Tile(coordinate) {
    this->path = "./../../../res/hexagon-pack/PNG/mountain.png"
}

void Mountain::Effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}