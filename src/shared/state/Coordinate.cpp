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


bool Coordinate::operator==(const Coordinate &rhs) {
    return (this->row == rhs.row) && (this->column == rhs.column);
}
