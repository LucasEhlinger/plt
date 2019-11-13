#include "King.h"

using namespace ::state;

King::King(state::Coordinate coordinate) : Pawn(coordinate, "King") {
    number_type = 4;
    lifePoints = 9;

    //TODO : A completer avec les valeurs reeles de jeu.
    resources = Resources(0, 0, 0, 0);
    stats = Stats(7, 0, 0, 0);
}

void King::modifyRot() {
    resources.rot -= 1;
}