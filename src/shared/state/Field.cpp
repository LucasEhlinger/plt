#include "Field.h"
using namespace ::state;

Field::Field(state::Coordinate coordinate) : Tile(coordinate){
    this->path = "./../../../res/hexagon-pack/PNG/field.png"
}
