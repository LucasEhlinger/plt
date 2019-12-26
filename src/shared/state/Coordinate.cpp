#include "Coordinate.h"
#include <stdexcept>      // std::out_of_range

using namespace ::state;

Coordinate::Coordinate(int row, int column) : row(row), column(column) {
    if (row >= 13 || column >= 13) {
        throw std::out_of_range("inLinePos<X>::at() : index is out of range");
    }
}

void Coordinate::setCoord(int row, int column) {
    if (row < 13 || column < 13) {
        setRow(row);
        setColumn(column);
    } else {
        throw std::out_of_range("inLinePos<X>::at() : index is out of range");

    }
}

void Coordinate::setCoord(int inLinePos) {
    // on a 13*13 map
    if (inLinePos < (13 * 13)) {
        int row = (inLinePos / 13);
        this->setColumn(inLinePos - (13 * row));
        this->setRow(row);

    } else {
        throw std::out_of_range("inLinePos<X>::at() : index is out of range");
    }
}

int Coordinate::getRow() {
    return this->row;
}

int Coordinate::getColumn() {
    return this->column;
}

void Coordinate::setRow(int row) {
    this->row = row;
}

void Coordinate::setColumn(int column) {
    this->column = column;
}

int Coordinate::getCoordInLine() {
    return (row * 13) + column;
}

std::array<int, 3> Coordinate::evenr_to_cube() {
    int x = this->getColumn() - (this->getRow() + (this->getRow() & 1)) / 2;
    int z = this->getRow();
    int y = -x - z;
    return std::array<int, 3>{x, y, z};
}

int Coordinate::distance(state::Coordinate goal) {
    std::array<int, 3> this_c = this->evenr_to_cube();
    std::array<int, 3> goal_c = goal.evenr_to_cube();
    return std::max(std::max(std::abs(this_c.at(0) - goal_c.at(0)), std::abs(this_c.at(1) - goal_c.at(1))),
                    std::abs(this_c.at(2) - goal_c.at(2)));
}

bool Coordinate::operator==(const Coordinate &rhs) {
    return (this->row == rhs.row) && (this->column == rhs.column);
}
