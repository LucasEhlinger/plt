#include "../state.h"
#include <string>
#include <iostream>
#include <array>

#define HEIGHT 13
#define WIDTH 13
#define MID_HEIGHT 6
#define MID_WIDTH 6

using namespace ::state;

Board::Board() {
    this->day = true;
}

Board::Board(const state::Board &board) {
    this->day = board.day;

    if (board.tiles.size() != 0) {
        for (int i = 0; i < board.tiles.size(); i++) {
            tiles.at(i) = board.tiles[i];
        }
        //this->tiles(new std::array<std::unique_ptr<Tile>,13*13> (board.tiles))
        this->pawns = board.pawns;
    }
}

/**
 * Pass from day to night and vice versa
 */
void Board::changeTime() {
    this->day = !this->day;
}

state::Pawn& Board::playingPawn() {
    for (int i = 0; i < pawns.size(); ++i) {
        if (pawns.at(i).isPlaying) {
            return pawns[i];
        }
    }
    return pawns[0];
}

std::vector<state::Coordinate> Board::matrixAv_Tile(state::Pawn & pawn) {
    std::vector<state::Coordinate> av_tiles;
    bool row_up = false;
    bool row_down = false;
    bool col_up = false;
    bool col_down = false;

    int x = pawn.getCoordinate().getRow();
    int y = pawn.getCoordinate().getColumn();
    int ap = pawn.getAP();

    if (x < 12)
        row_up = true;
    if (y < 12)
        col_up = true;
    if (x > 0)
        row_down = true;
    if (y > 0)
        col_down = true;

    if (row_down)
        if (tiles.at((x - 1) * HEIGHT + y).exist &&
            ap + tiles.at((x - 1) * HEIGHT + y).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x - 1, y});
    if (row_up)
        if (tiles.at((x + 1) * HEIGHT + y).exist &&
            ap + tiles.at((x + 1) * HEIGHT + y).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x + 1, y});
    if (col_down)
        if (tiles.at(x * HEIGHT + (y - 1)).exist &&
            ap + tiles.at(x * HEIGHT + (y - 1)).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x, y - 1});
    if (col_up)
        if (tiles.at(x * HEIGHT + (y + 1)).exist &&
            ap + tiles.at(x * HEIGHT + (y + 1)).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x, y + 1});
    if (row_down && col_up)
        if (tiles.at((x - 1) * HEIGHT + (y + 1)).exist &&
            ap + tiles.at((x - 1) * HEIGHT + (y + 1)).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x - 1, y + 1});
    if (row_up && col_down)
        if (tiles.at((x + 1) * HEIGHT + (y - 1)).exist &&
            ap + tiles.at((x + 1) * HEIGHT + (y - 1)).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x + 1, y - 1});
    return av_tiles;
}


void Board::nextTurn() {
    for (int i = 0; i < pawns.size(); ++i) {
        if (pawns.at(i).isPlaying) {
            pawns[i].isPlaying = false;
            if (i + 1 >= pawns.size()) {
                pawns[0].setAP(1);
                pawns[0].isPlaying = true;
            } else {
                pawns[i + 1].setAP(1);
                pawns[i + 1].isPlaying = true;
            }
            break;
        }
    }
}


void Board::generate() {

    srand(time(NULL));

    for (int i = 0; i < (HEIGHT * WIDTH) - 1; ++i) {
        switch (rand() % 7) {
            case 0:
                // Ruin
                tiles[i] = Ruin();
                break;
            case 1:
                // Field
                tiles[i] = Field();
                break;
            case 2:
                // Forest
                tiles[i] = Forest();
                break;
            case 3:
                // Mountain
                tiles[i] = Mountain();
                break;
            case 4:
                // StoneAge
                tiles[i] = StoneAge();
                break;
            case 5:
                // Swamp
                tiles[i] = Swamp();
                break;
            case 6:
                // Colony
                tiles[i] = Colony();
                break;
        }
    }
    for (int line = 0; line < MID_HEIGHT; ++line) {
        for (int column = 0; column < WIDTH; ++column) {
            if (column < (WIDTH / 2) - line) {
                tiles[line * HEIGHT + column] = Tile();
                tiles[((HEIGHT - 1) - line) * HEIGHT + (WIDTH - 1) - column] = Tile();
            }
        }
    }
    for (int i = 0; i < HEIGHT; i += MID_HEIGHT) {
        for (int j = 0; j < WIDTH; j += MID_WIDTH) {
            for (int k = 0; k < 2; ++k) {
                if (i == 0 && k == 1)
                    tiles[7] = Field();
                else if (i != 0 || k != 0) {
                    tiles[(std::max(i - 1, 0) + k) * HEIGHT + j] = Field();
                    tiles[(std::max(i - 1, 0) + k) * HEIGHT + std::min(j + 1, WIDTH - 1)] = Field();
                }
                if (i != HEIGHT - 1 || k != 1) {
                    tiles[(std::min(i + 1, HEIGHT - 1) - k) * HEIGHT + j] = Field();
                    tiles[(std::min(i + 1, HEIGHT - 1) - k) * HEIGHT + std::max(j - 1, 0)] = Field();
                }
            }
            tiles[i * HEIGHT + j] = Start();
        }
    }

    for (int i = 0; i < 2; ++i) {
        //Castle of the king
        tiles[(MID_HEIGHT - 1 + i) * HEIGHT + MID_WIDTH] = Castle();
        tiles[(MID_HEIGHT - 1 + i) * HEIGHT + MID_WIDTH + 1] = Castle();
        tiles[(MID_HEIGHT + 1 - i) * HEIGHT + MID_WIDTH] = Castle();
        tiles[(MID_HEIGHT + 1 - i) * HEIGHT + MID_WIDTH - 1] = Castle();
    }
}
