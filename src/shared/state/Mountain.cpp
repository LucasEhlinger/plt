#include "Mountain.h"
using namespace ::state;

Mountain::Mountain(state::Coordinate coordinate):Tile(coordinate) {}

void Mountain::Effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
}