#include "Pawn.h"

#include <list>
#include <algorithm>
#include <iterator>
#include <random>
#include <functional>
#include <SFML/System.hpp>

using namespace ::state;

Pawn::Pawn(state::Coordinate position, std::string name) : coordinate(position), name(name),
                                                           stats(0, 0, 0, 0),
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
    if (this->lifePoints <= 0) {
        // Le if suivant me fait penser qu'au final le "name" des pawns ne sert strictement à rien, à voir pour le virer
        if (this->starting_tile.getCoordInLine() != state::Coordinate{0, 0}.getCoordInLine()) { // sera peut-être modifié pour mettre un if sur le number_type à la place
            this->setCoordinate(this->starting_tile);
            this->setAP(0);
        }
        // En fait ça serait mieux de virer ça d'ici et le gérer avec l'engine plutôt
        //TODO le else de ses grands morts
        // par "ses grands morts", je veux dire qu'il faut pouvoir notifier que le pion qui tombe à 0 LP, n'étant pas un joueur d'après le if ligne 40, doit être viré de la liste de pions
    }
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

void Pawn::setCoordinate(const Coordinate &coordinate) {
    this->coordinate = coordinate;
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

// TODO: adapt dia
std::array<int, 2> Pawn::attack(state::Pawn attacked, bool day, int mountain) {
    int pawn1Sword = 0;
    int pawn2Sword = 0;

    int pawn1Shield = 0;
    int pawn2Shield = mountain;

    int pawn1Dice = this->getCombativeness();
    int pawn2Dice = attacked.getCombativeness();

    if (this->getRot() >= 5 || attacked.getRot() >= 5)
        if (this->getRot() > attacked.getRot())
            pawn1Dice += attacked.getRot();
        else
            pawn2Dice += this->getRot();

    int rolled = 0;
    static auto gen = std::bind(std::uniform_int_distribution<>(1, 6), std::default_random_engine());

    if (this->resources.rot >= 5 && attacked.resources.rot < this->resources.rot) {
        pawn1Dice += attacked.resources.rot;
    }

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

    return std::array<int, 2>{pawn1Sword - pawn2Shield, pawn2Sword - pawn1Shield};
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

void Pawn::modifyStats(int combativeness = 0, int vitality = 0, int presenceOfMind = 0, int spiritualityint = 0) {
    stats.combativeness += combativeness;
    stats.vitality += vitality;
    stats.presenceOfMind += presenceOfMind;
    stats.spirituality += spiritualityint;
}

state::Resources Pawn::getResources() {
    return resources;
}

void Pawn::setResources(const class state::Resources &resources) {
    this->resources = resources;
}

void Pawn::setStats(const class state::Stats &stats) {
    this->stats = stats;
}

int Pawn::getCombativeness() {
    return stats.combativeness;
}

int Pawn::getVitality() {
    return stats.vitality;
}

int Pawn::getPresenceOfMind() {
    return stats.presenceOfMind;
}

int Pawn::getSpirituality() {
    return stats.spirituality;
}
