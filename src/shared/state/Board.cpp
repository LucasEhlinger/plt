#include "../state.h"
#include <iostream>
#include <string>
#include <fstream>

#define HEIGTH 13

using namespace ::state;

Board::Board(){
    this->day = true;

    pawns.emplace_back(Player{Coordinate{0, 0}, "player1"});

    srand(time(NULL));

    for (int line = 0; line < HEIGTH; ++line) {
        std::vector<std::unique_ptr<Tile>> tempTiles;
        for (int column = 0; column < HEIGTH; ++column) {
            switch (rand() % 7 + 1) {
                case 1:
                    // Swamp
                    // tempString.emplace_back("5");
                    tempTiles.emplace_back(Swamp{});

                    break;
                case 2:
                    // Forest
                    // tempString.emplace_back("2");
                    tempTiles.emplace_back(Forest{});

                    break;
                case 3:
                    // Ruin
                    // tempString.emplace_back("0");
                    tempTiles.emplace_back(Ruin{});
                    break;
                case 4:
                    // Colony
                    // tempString.emplace_back("6");
                    tempTiles.emplace_back(Colony{});
                    break;
                case 5:
                    // Mountain
                    // tempString.emplace_back("3");
                    tempTiles.emplace_back(Mountain{});
                    break;
                case 6:
                    // Field
                    // tempString.emplace_back("1");
                    tempTiles.emplace_back(Field{});
                    break;
                case 7:
                    // StoneAge
                    // tempString.emplace_back("4");
                    tempTiles.emplace_back(StoneAge{});
                    break;
            }
        }
        tiles.emplace_back(tempTiles);
    }
    //TODO : Optimiser ce code
    // Triangle haut gauche, pour hexagone
    for (int line = 0; line < (HEIGTH - 1) / 2; ++line) {
        for (int column = 0; column < ((HEIGTH - 1) / 2) - line; ++column) {
            //tilesTypes[line][column] = "9";
            tiles[line][column] = nullptr;
        }
    }

    // Triangle bas droite
    int itt = 0;
    for (int line = (HEIGTH - 1) / 2; line < HEIGTH; ++line) {
        ++itt;
        for (int column = HEIGTH - 1; column > HEIGTH - itt; --column) {
            //tilesTypes[line][column] = "9";
            tiles[line][column] = nullptr;
        }
    }
}

/**
 * Pass from day to night and vice versa
 */
void Board::changeTime() {
    this->day = !this->day;
}