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


bool Pawn::attack(state::Pawn attacked, bool day) {
    int pawn1Sword = 0;
    int pawn2Sword = 0;

    int pawn1Shield = 0;
    int pawn2Shield = 0;

    int pawn1Dice = 3;
    int pawn2Dice = 3;

    int rolled = 0;
    static auto gen = std::bind(std::uniform_int_distribution<>(1,6),std::default_random_engine());
    //Pawn 1
    while (rolled != pawn1Dice) {
        ++rolled;
        switch (gen()) {
            case 1:
                ++pawn1Sword;
                break;
            case 2:
                ++pawn1Shield;
                break;
            case 3:
                if (day) ++pawn1Sword;
                break;
            case 4:
                if (!day) ++pawn1Sword;
                break;
            case 5:
                if (this->getRot() >= 5) {
                    ++pawn1Dice;
                    ++pawn1Sword;
                }
                break;
            case 6:
                if (this->getRot() < 5) {
                    ++pawn1Dice;
                    ++pawn1Sword;
                }
                break;
        }
    }
    rolled = 0;

    //Pawn 2
    while (rolled != pawn2Dice) {
        ++rolled;
        switch (gen()) {
            case 1:
                ++pawn2Sword;
                break;
            case 2:
                ++pawn2Shield;
                break;
            case 3:
                if (day) ++pawn2Sword;
                break;
            case 4:
                if (!day) ++pawn2Sword;
                break;
            case 5:
                if (attacked.getRot() >= 5) {
                    ++pawn2Dice;
                    ++pawn2Sword;
                }
                break;
            case 6:
                if (attacked.getRot() < 5) {
                    ++pawn2Dice;
                    ++pawn2Sword;
                }
                break;
        }
    }
    unsigned int LP1 = pawn2Sword - pawn1Shield;
    unsigned int LP2 = pawn1Sword - pawn2Shield;

    if (LP1 > LP2){
        return true;
    }
    return false;
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