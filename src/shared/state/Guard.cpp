#include "Guard.h"

using namespace ::state;

Guard::Guard(state::Coordinate position, std::string name, bool on_duty) : Pawn(position, name) {
    number_type = 5;
    this->on_duty = on_duty;
}
