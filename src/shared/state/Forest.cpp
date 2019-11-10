#include "Forest.h"

using namespace ::state;

Forest::Forest() : Tile() {
    number_type = 2;
}

void Forest::effect(Pawn &pawn) {
    pawn.modifyAP(moveCost);
    /*
 * if night then set visibility to false.
 */
}
