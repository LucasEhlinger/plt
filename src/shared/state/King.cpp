#include "King.h"

using namespace ::state;

King::King(state::Coordinate coordinate) : Pawn(coordinate, "King") {
    number_type = 4;
    AP_max = 0;

    resources = Resources(0, 0, 0, 1);
    stats = Stats(7, 9, 0, 0);

    lifePoints = stats.getVitality();
}

void King::modifyRot() {
    resources.rot -= 1;
}