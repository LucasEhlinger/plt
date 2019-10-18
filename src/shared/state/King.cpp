#include "King.h"
using namespace ::state;

King::King(state::Coordinate coordinate) : Tile(coordinate){
    this->path = "./../../../res/hexagon-pack/PNG/castle.png"
}
