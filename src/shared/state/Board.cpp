#include "../state.h"
#include <string>
#include <iostream>

#define HEIGHT 13

using namespace ::state;

Board::Board() {
    this->day = true;
}

/**
 * Pass from day to night and vice versa
 */
void Board::changeTime() {
    this->day = !this->day;
}

void Board::generate() {

    srand(time(NULL));

    for (int i = 0; i < (HEIGHT * HEIGHT) - 1; ++i) {
        switch (rand() % 7 + 1) {
            case 1:
                // Swamp
                tiles[i] = new Swamp();
                break;
            case 2:
                // Forest
                tiles[i] = new Forest();
                break;
            case 3:
                // Ruin
                tiles[i] = new Ruin();
                break;
            case 4:
                // Colony
                tiles[i] = new Colony();
                break;
            case 5:
                // Mountain
                tiles[i] = new Mountain();
                break;
            case 6:
                // Field
                tiles[i] = new Field();
                break;
            case 7:
                // StoneAge
                tiles[i] = new StoneAge();
                break;
        }
    }
    for (int line = 0; line < ((HEIGHT - 1) / 2); ++line) {
        for (int column = 0; column < HEIGHT; ++column) {
            if (column < (HEIGHT / 2) - line) {
                tiles[line * HEIGHT + column] = nullptr;
                tiles[((HEIGHT - 1) - line) * HEIGHT + (HEIGHT - 1) - column] = nullptr;
            }
        }
    }

    /*
     // Affichage pour verification
     for(int i = 0; i< HEIGHT ; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            if (tiles[(i* HEIGHT) + j] != nullptr)
                std::cout << tiles[(i* HEIGHT) + j]->path + " ";
            else
                std::cout << "Nu ";
        }
        std::cout << "\n";
    }*/
}