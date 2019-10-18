#include "Mountain.h"

using namespace ::state;

Mountain::Mountain(state::Coordinate coordinate) : Tile(coordinate) {
    this->path = "./../../../res/hexagon-pack/PNG/mountain.png";
    moveCost = -2;
}

void Mountain::Effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}