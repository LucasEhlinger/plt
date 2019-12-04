#include "Pawn.h"

#include <list>
#include <algorithm>
#include <iterator>
#include <random>
#include <functional>

using namespace ::state;

Pawn::Pawn(state::Coordinate position, std::string name) : coordinate(position), name(name), stats(0, 0, 0, 0),
                                                           resources(0, 0, 0, 0) {
    lifePoints = 0;
    actionPoints = 0;
    isHuman = false;
    isPlaying = false;
}

void Pawn::move(state::Coordinate coordinate) {
    this->coordinate = coordinate;
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
    return this->resources.rot;
}


bool Pawn::attack(state::Pawn attacked) {
    static auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
    return gen();
}

/**
 * equality operator to test if too players are the same.
 * @param rhs state::Pawn
 * @return bool
 */
bool Pawn::operator==(state::Pawn &rhs) {
    return rhs.coordinate == coordinate &&
           rhs.isHuman == isHuman &&
           rhs.resources == resources &&
           rhs.lifePoints == lifePoints &&
           rhs.actionPoints == actionPoints &&
           rhs.stats == stats &&
           rhs.name == name;
}

void Pawn::modifyStats (int com = 0, int vit = 0, int pom = 0, int spi = 0) {
    this->stats.combativeness += com;
    this->stats.vitality += vit;
    this->stats.presenceOfMind += pom;
    this->stats.spirituality += spi;
}

state::Resources Pawn::getResources() {
    return this->resources;
}