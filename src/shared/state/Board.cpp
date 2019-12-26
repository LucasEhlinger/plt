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

state::Pawn &Board::playingPawn() {
    for (int i = 0; i < pawns.size(); ++i)
        if (pawns.at(i).isPlaying)
            return pawns[i];

    return pawns[0];
}

std::vector<state::Coordinate> Board::matrixAv_Tile(state::Pawn &pawn) {
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

    if (pawn.on_duty) {
        std::vector<state::Coordinate> duty_tiles;
        for (state::Coordinate tile : av_tiles)
            if (tiles.at(tile.getCoordInLine()).number_type == 8 &&
                tile.getCoordInLine() != state::Coordinate{6, 6}.getCoordInLine())
                duty_tiles.emplace_back(tile);
        return duty_tiles;
    }
    return av_tiles;
}


void Board::nextTurn() {
    for (int i = 0; i < pawns.size(); ++i) {
        if (pawns.at(i).isPlaying) {
            pawns[i].isPlaying = false;
            if (i + 1 >= pawns.size()) {
                pawns[0].setAP(0);
                pawns[0].isPlaying = true;
                this->changeTime();
            } else {
                if (pawns[i + 1].number_type == 5 || pawns[i + 1].number_type == 6)
                    pawns[i + 1].setAP(2);
                else
                    pawns[i + 1].setAP(3);
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
    for (int i = 0; i < HEIGHT; i += MID_HEIGHT)
        for (int j = 0; j < WIDTH; j += MID_WIDTH) {
            tiles[i * HEIGHT + j] = Start();
            for (int k = -1; k <= 1; ++k)
                for (int l = -1; l <= 1; ++l)
                    if (i + k >= 0 && i + k < HEIGHT && j + l >= 0 && j + l < WIDTH && k != l &&
                        tiles[(i + k) * HEIGHT + (j + l)].exist)
                        tiles[(i + k) * HEIGHT + (j + l)] = Field();
        }

    for (int i = 0; i < 2; ++i) {
        //Castle of the king
        tiles[(MID_HEIGHT - 1 + i) * HEIGHT + MID_WIDTH] = Castle();
        tiles[(MID_HEIGHT - 1 + i) * HEIGHT + MID_WIDTH + 1] = Castle();
        tiles[(MID_HEIGHT + 1 - i) * HEIGHT + MID_WIDTH] = Castle();
        tiles[(MID_HEIGHT + 1 - i) * HEIGHT + MID_WIDTH - 1] = Castle();
    }
}
