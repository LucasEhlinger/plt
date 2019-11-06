#include "Forest.h"
using namespace ::state;

Forest::Forest() : Tile(){
    this->path = "./../../../res/hexagon-pack/PNG/forest.png";
}

void Forest::effect(Pawn &pawn) {
    pawn.modifyAP(moveCost);
    /*
 * if night then set visibility to false.
 */
}
