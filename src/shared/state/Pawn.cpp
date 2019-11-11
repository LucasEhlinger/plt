#include "Pawn.h"

#include <list>
#include <algorithm>
#include <iterator>

using namespace ::state;

Pawn::Pawn(state::Coordinate position, std::string name) : coordinate(position), name(name) {
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
 * get the number of actionPoints of the player
 * @return int action points
 */
int Pawn::getAP() {
    return this->actionPoints;
}

/**
 * set the action points of the player
 * @param value int action points
 */
void Pawn::setAP(int value) {
    this->actionPoints = value;
}

/**
 * get player coordinates
 * @return Coordinate of pawn
 */
Coordinate Pawn::getCoordinate() {
    return this->coordinate;
}

/**
 * get the life points of the player
 * @return int number of life points
 */
int Pawn::getLP() {
    return this->lifePoints;
}

/**
 * set life points
 * @param LifePoints int
 */
void Pawn::setLP(int LifePoints) {
    this->lifePoints = LifePoints;
}

/**
 * get rot of the pawn
 * @return int rot
 */
int Pawn::getRot() {
    return this->resources->rot;
}

/**
 * equality operator to test if too players are the same.
 * @param rhs state::Pawn
 * @return bool
 */
bool Pawn::operator==(state::Pawn &rhs) {
    return rhs.coordinate == coordinate &&
           *rhs.resources == *resources &&
           rhs.lifePoints == lifePoints &&
           rhs.actionPoints == actionPoints &&
           *rhs.stats == *stats &&
           rhs.name == name;
}