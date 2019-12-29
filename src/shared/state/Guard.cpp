#include "Guard.h"

using namespace ::state;

Guard::Guard(state::Coordinate position, std::string name, bool on_duty) : Pawn(position, name) {
    number_type = 5;
    AP_max = 2;
    this->on_duty = on_duty;

    resources = Resources(0, 0, 0, 0);
    stats = Stats(4, 5, 0, 0);

    lifePoints = stats.getVitality();
}
