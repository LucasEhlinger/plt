#include "Pawn.h"

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

// Observers
void Pawn::notify() {
    std::for_each(observers.begin(), observers.end(), [](IObserver &obs) {
        //obs.update();
    });
}

void Pawn::add(state::IObserver observer) {
    this->observers.push_back(observer);
}

void Pawn::remove(state::IObserver observer) {

}