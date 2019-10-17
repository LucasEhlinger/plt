#include "Board.h"

using namespace ::state;

Board::Board() {
    //c'est totalement temporaire ... vous imaginez bien qu'on va pas laisser ça comme ça !
    for (int i; i < 13; i++) {
        for (int y; y < 13; y++) {
            tiles[i][y] = NULL;
        }
    }
    day = true;
    //TODO : projet
}

/**
 * Pass from day to night and vice versa
 */
void Board::changeTime() {
    day = !day;
}

/**
 * Add a pawn to the Game
 * @param pawn Pawn added pawn
 */
void Board::addPawn(state::Pawn &pawn) {
    pawns.push_back(pawn);
}