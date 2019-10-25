#include "Board.h"

using namespace ::state;

Board::Board() {
    this->day = true;

    //c'est totalement temporaire ... vous imaginez bien qu'on va pas laisser ça comme ça !
    /*
    int i, j;
    int t_edge1 = 0;
    int t_edge2 = 6;
    int t_edge3 = 12;

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

void Board::notify() {
    for (auto obs = observers.begin(); obs != observers.end(); ++obs) {
        obs.base()->update(this);
    }
}

void Board::add(state::IObserver observer) {
    this->observers.push_back(observer);
}

void Board::remove(state::IObserver observer) {

}