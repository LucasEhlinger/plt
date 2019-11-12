#include "Guard.h"

using namespace ::state;

Guard::Guard(state::Coordinate position, std::string name) : Pawn(position, name) {
    number_type = 5;
}
