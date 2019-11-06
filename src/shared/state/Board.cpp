#include "../state.h"
#include <iostream>
#include <string>
#include <fstream>

#define HEIGTH 13

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

std::vector<std::vector<std::string>> Board::generate() {
    std::vector<std::vector<std::string>> tilesTypes;
    srand(time(NULL));

    for (int line = 0; line < HEIGTH; ++line) {
        std::vector<std::string> tempString;
        for (int column = 0; column < HEIGTH; ++column) {
            switch (rand() % 7 + 1) {
                case 1:
                    //Swamp
                    tempString.emplace_back("Sw");
                    break;
                case 2:
                    //Forest
                    tempString.emplace_back("Fo");
                    break;
                case 3:
                    //Ruin
                    tempString.emplace_back("Ru");
                    break;
                case 4:
                    //Colony
                    tempString.emplace_back("Co");
                    break;
                case 5:
                    //Mountain
                    tempString.emplace_back("Mo");
                    break;
                case 6:
                    //Field
                    tempString.emplace_back("Fi");
                    break;
                case 7:
                    //StoneAge
                    tempString.emplace_back("SA");
                    break;
            }
        }
        tilesTypes.emplace_back(tempString);
    }
    //TODO : Optimiser ce code
    // Triangle haut gauche, pour hexagone
    for (int line = 0; line < (HEIGTH - 1) / 2; ++line) {
        for (int column = 0; column < ((HEIGTH - 1) / 2) - line; ++column) {
            tilesTypes[line][column] = "Nu";
        }
    }

    // Triangle bas droite
    int itt = 0;
    for (int line = (HEIGTH - 1) / 2; line < HEIGTH; ++line) {
        ++itt;
        for (int column = HEIGTH - 1; column > HEIGTH - itt; --column) {
            tilesTypes[line][column] = "Nu";
        }
    }

    return tilesTypes;
}

void Board::generateFile(std::vector<std::vector<std::string>> generated, std::string filePath) {
    std::ofstream outfile(filePath);

    for (std::size_t lines = 0; lines < generated.size(); ++lines) {
        for (std::size_t column = 0; column < generated[lines].size(); ++column) {
            std::string st = generated[lines][column];
            outfile << st + " ";
        }
        outfile << "\n";
    }

    outfile << std::endl;
    outfile.close();
}