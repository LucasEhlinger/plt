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

    // set NULL spots in the tile table.
    i = t_edge1;
    j = t_edge2;
    while(i != t_edge2+1) {
        for(int k = t_edge1; k<j; k++) {
            tiles[i][k] = nullptr;
        }
        j-=1;
        i+=1;
    }
    i = t_edge3;
    j = t_edge2;
    while(i != t_edge2) {
        for(int k = t_edge3; k>j; k--) {
            tiles[i][k] = nullptr;
        }
        j+=1;
        i-=1;
    }*/
}

/**
 * Pass from day to night and vice versa
 */
void Board::changeTime() {
    this->day = !this->day;
}

void Board::notify() {
    std::for_each(observers.begin(), observers.end(), [](IObserver &observer) {
        //observer.update();
    });
}

void Board::add(state::IObserver observer) {
    this->observers.push_back(observer);
}

void Board::remove(state::IObserver observer) {

}