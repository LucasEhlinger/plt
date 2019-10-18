#include "King.h"

using namespace ::state;

King::King(state::Coordinate coordinate) : Tile(coordinate), Pawn(coordinate) {
    this->path = "./../../../res/hexagon-pack/PNG/castle.png";
    combativeness = 7;
    rot = 1;
    lifePoints = 9;
    moveCost = -3;
}

void King::modifyRot() {
    rot -= 1;
}

void King::modifyLP(int offset) {
    lifePoints += offset;
}
