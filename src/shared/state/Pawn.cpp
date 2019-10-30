#include "Pawn.h"

#include <list>
#include <algorithm>
#include <iterator>

using namespace ::state;

Pawn::Pawn(state::Coordinate position) : coordinate(position) {
    lifePoints = 0;
    actionPoints = 0;
    resources = new Resources(0, 0, 0, 0);
    stats = new Stats(0, 0, 0, 0);
}

/**
 * Remove or add action points depending of argument passed
 * @param offset int number of points added or deleted (minus)
 */
void Pawn::modifyAP(int offset) {
    this->actionPoints += offset;
}

/**
 * Remove or add life points depending of argument passed
 * @param offset int number of points added or deleted (minus)
 */
void Pawn::modifyLP(int offset) {
    this->lifePoints += offset;
}

/**
 *
 * @return
 */
int Pawn::getAP() {
    return this->actionPoints;
}

/**
 *
 * @param value
 */
void Pawn::setAP(int value) {
    this->actionPoints = value;
}

Coordinate Pawn::getCoordinate() {
    return this->coordinate;
}

int Pawn::getLP() {
    return this->lifePoints;
}

void Pawn::setLP(int LifePoints) {
    this->lifePoints = LifePoints;
}

int Pawn::getRot() {
    return this->resources->rot;
}

bool Pawn::operator==(state::Pawn &rhs) {
    return rhs.coordinate == coordinate &&
           rhs.resources == resources &&
           rhs.lifePoints == lifePoints &&
           rhs.actionPoints == actionPoints &&
           rhs.stats == stats;
}