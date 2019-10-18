#include "King.h"
using namespace ::state;

King::King(state::Coordinate coordinate) : Tile(coordinate){
    this->path = "./../../../res/hexagon-pack/PNG/castle.png"
}

void modifyRot(){
    this->rot -= 1;
}

void modifyLP(int offset){
    this->lifePoints += offset;
}
