#include "Forest.h"
using namespace ::state;

Forest::Forest() : Tile(){
    this->path = "Fo";
}

void Forest::effect(Pawn &pawn) {
    pawn.modifyAP(moveCost);
    /*
 * if night then set visibility to false.
 */
}
