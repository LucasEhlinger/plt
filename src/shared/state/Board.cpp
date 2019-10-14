#include "Board.h"

bool state::Board::isDay() {
    if ((this->time > this->sunrise) || (this->time < this->sunset)) {
        return true;
    }
    return false;
}