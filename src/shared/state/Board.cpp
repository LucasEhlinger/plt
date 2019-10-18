#include "Board.h"

using namespace ::state;

Board::Board() {
    //c'est totalement temporaire ... vous imaginez bien qu'on va pas laisser ça comme ça !
//    for (int i; i < 13; i++) {
//        for (int y; y < 13; y++) {
//            tiles[i][y] = NULL;
//        }
//    }
//    day = true;
//
//    int i, j;
//    int t_edge1 = 0;
//    int t_edge2 = 6;
//    int t_edge3 = 12;
//    for(i=t_edge1; i<t_edge2; i++){
//
//    }
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