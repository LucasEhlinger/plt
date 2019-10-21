#include "Board.h"

using namespace ::state;

Board::Board() {
    //will be used when Board is initialized, to be kept in the back of our heads
    /*this->day = true;

    int row_length = 13;
    int nb_rows = 13;
    int len_null = 6;
    int position;

    for(int i; i<row_length; ++i){
        for(int j; j<nb_rows; ++j){
            position = i+row_length*j;
            if(len_null-i>0){
                if(j<len_null-i+1)
                    tiles[position] = nullptr;
                else
                    tiles[position] = std::unique_ptr<Tile>(new Tile(Coordinate{i,j}));
            }
            else if(i-len_null>0){
                if(j>i-len_null+1)
                    tiles[position] = nullptr;
                else
                    tiles[position] = std::unique_ptr<Tile>(new Tile(Coordinate{i,j}));
            }
            else
                tiles[position] = std::unique_ptr<Tile>(new Tile(Coordinate{i,j}));
        }
    }*/
}

/**
 * Pass from day to night and vice versa
 */
void Board::changeTime() {
    this->day = !this->day;
}