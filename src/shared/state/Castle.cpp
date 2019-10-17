#include "Castle.h"

using namespace ::state;

Castle::Castle(state::Coordinate coordinate) : Tile(coordinate) {}

/**
 * Apply effects of the Castle on the pawn
 * @param pawn Pawn affected pawn
 */
void Castle::Effect(Pawn &pawn) {
    pawn.setAP(0);
}