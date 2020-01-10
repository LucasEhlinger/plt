#include "Tile.h"

using namespace ::state;

Tile::Tile() {
    number_type = 9;
}

/**
 * Apply effects of the tile on the pawn
 * @param pawn Pawn affected pawn
 */
void Tile::effect(state::Pawn &pawn) {
    pawn.modifyAP(moveCost);
    switch (number_type){
        case 8: //Castle
            pawn.setAP(0);
            break;
        case 5: //Swamp
            pawn.modifyLP(-1);
            break;
        case 4: //StoneAge
            if (pawn.getRot() < 5)
                pawn.modifyLP(+1);
            else if (pawn.number_type == 6)
                pawn.setLP(0);
            else
                pawn.modifyLP(-1);
            break;
        case 0: //Ruin
            break;
    }
}

int Tile::getMoveCost() const {
    return this->moveCost;
}

bool Tile::operator==(state::Tile &rhs) {
    return rhs.moveCost == moveCost &&
           rhs.observers.size() == observers.size();
}