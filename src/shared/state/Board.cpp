#include "Board.h"

using namespace ::state;

Board::Board() {
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
 * Add a tile to the Board Game.
 * @param tile Tile added tile
 */
void Board::addTile(state::Tile tile) {
    tiles.push_back(tile);
}

/**
 * Add a pawn to the Game
 * @param pawn Pawn added pawn
 */
void Board::addPawn(state::Pawn pawn) {
    pawns.push_back(pawn);
}