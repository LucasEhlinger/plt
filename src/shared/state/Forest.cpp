#include "Forest.h"

using namespace ::state;

void Forest::Effect(Pawn &pawn) {
    pawn.modifyAP(moveCost);
    /*
 * if night then set visibility to false.
 */
}