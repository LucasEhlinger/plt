#include "Coordinate.h"

using namespace ::state;

Coordinate::Coordinate(int row, int column) : row(row), column(column) {}

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

void Coordinate::setCoord(int row, int column) {
    setRow(row);
    setColumn(column);
}

bool Coordinate::operator==(const Coordinate &rhs) {
    return (this->row == rhs.row) && (this->column == rhs.column);
}
