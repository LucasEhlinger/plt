#include "Bane.h"

using namespace ::state;

Bane::Bane(state::Coordinate position, std::string name) : Pawn(position, name) {
    number_type = 6;
    AP_max = 1;

    resources = Resources(0, 0, 0, 5);
    stats = Stats(5, 4, 0, 0);

    lifePoints = stats.getVitality();
}