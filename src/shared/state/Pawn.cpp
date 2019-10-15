#include "Pawn.h"
using namespace ::state;

Pawn::Pawn(state::Coordinate position):coordinate(position) {}

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
int Pawn::getAP(){
    return this->actionPoints;
}

/**
 *
 * @param value
 */
void Pawn::setAP(int value) {
    this->actionPoints = value;
}

/**
 *
 * @param board
 * @return std::vector<Coordinate>
 */
std::vector<Coordinate> Pawn::checkNeighbors(state::Board board) {

}