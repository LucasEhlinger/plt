#include "Bane.h"

using namespace ::state;

Bane::Bane(state::Coordinate position, std::string name) : Pawn(position, name) {
    number_type = 6;
}