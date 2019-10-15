#include "Pawn.h"
using namespace ::state;

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
 * @param board
 * @return std::vector<Coordinate>
 */
std::vector<Coordinate> Pawn::checkNeighbors(state::Board board) {

}