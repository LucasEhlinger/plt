#include "Tile.h"

using namespace ::state;

void Tile::Effect(state::Pawn pawn){
    pawn.modifyAP(moveCost);
}
