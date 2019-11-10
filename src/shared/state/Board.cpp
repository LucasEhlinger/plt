#include "../state.h"
#include <string>
#include <iostream>

#define HEIGHT 13
#define WIDTH 13
#define MID_HEIGHT 6
#define MID_WIDTH 6

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

    for (int i = 0; i < (HEIGHT * WIDTH) - 1; ++i) {
        switch (rand() % 7) {
            case 0:
                // Ruin
                tiles[i] = new Ruin();
                break;
            case 1:
                // Field
                tiles[i] = new Field();
                break;
            case 2:
                // Forest
                tiles[i] = new Forest();
                break;
            case 3:
                // Mountain
                tiles[i] = new Mountain();
                break;
            case 4:
                // StoneAge
                tiles[i] = new StoneAge();
                break;
            case 5:
                // Swamp
                tiles[i] = new Swamp();
                break;
            case 6:
                // Colony
                tiles[i] = new Colony();
                break;
        }
    }
    for (int line = 0; line < MID_HEIGHT; ++line) {
        for (int column = 0; column < WIDTH; ++column) {
            if (column < (WIDTH / 2) - line) {
                tiles[line * HEIGHT + column] = nullptr;
                tiles[((HEIGHT - 1) - line) * HEIGHT + (WIDTH - 1) - column] = nullptr;
            }
        }
    }
    for (int i = 0; i < HEIGHT; i += MID_HEIGHT) {
        for (int j = 0; j < WIDTH; j += MID_WIDTH) {
            for (int k = 0; k < 2; ++k) {
                if (i == 0 && k == 1)
                    tiles[7] = new Field();
                else if (i != 0 || k != 0) {
                    tiles[(std::max(i - 1, 0) + k) * HEIGHT + j] = new Field();
                    tiles[(std::max(i - 1, 0) + k) * HEIGHT + std::min(j + 1, WIDTH - 1)] = new Field();
                }
                if (i != HEIGHT - 1 || k != 1) {
                    tiles[(std::min(i + 1, HEIGHT - 1) - k) * HEIGHT + j] = new Field();
                    tiles[(std::min(i + 1, HEIGHT - 1) - k) * HEIGHT + std::max(j - 1, 0)] = new Field();
                }
            }
            tiles[i * HEIGHT + j] = new Start();
        }
    }

    for (int i = 0; i < 2; ++i) {
        //Castle of the king
        tiles[(MID_HEIGHT - 1 + i) * HEIGHT + MID_WIDTH] = new Castle();
        tiles[(MID_HEIGHT - 1 + i) * HEIGHT + MID_WIDTH + 1] = new Castle();
        tiles[(MID_HEIGHT + 1 - i) * HEIGHT + MID_WIDTH] = new Castle();
        tiles[(MID_HEIGHT + 1 - i) * HEIGHT + MID_WIDTH - 1] = new Castle();
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