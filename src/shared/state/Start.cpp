#include "Start.h"
#include <iostream>
using namespace ::state;

Start::Start(Coordinate position):Tile(position) {}

void Start::Effect(state::Pawn* pawn) {
    pawn->modifyAP(moveCost);
    std::cout << pawn->getAP();
}