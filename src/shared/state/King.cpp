#include "King.h"

using namespace ::state;

King::King(state::Coordinate coordinate) : Pawn(coordinate, "King") {
    lifePoints = 9;
    moveCost = -3;

    //TODO : A completer avec les valeurs reeles de jeu.
    resources = new Resources(0, 0, 0, 0);
    stats = new Stats(7, 0, 0, 0);
}

void King::modifyRot() {
    resources->rot -= 1;
}