#include "Engine.h"
#include "state.h"

#define HEIGHT  13
#define WIDTH   13

using namespace engine;

Engine::Engine(state::Board &board) : board(&board) {
    state::Player player1{state::Coordinate{0, 6}, "player 1", true};
    player1.number_type = 1;
    player1.setAP(1);
    player1.isPlaying = true;

    state::Player player2{state::Coordinate{12, 6}, "player 2", false};
    player2.number_type = 2;

    state::King king{state::Coordinate{6, 6}};

    state::Guard guard1{state::Coordinate{8, 10}, "guard 1"};


    this->board->pawns.emplace_back(player1);
    this->board->pawns.emplace_back(player2);
    this->board->pawns.emplace_back(king);
    this->board->pawns.emplace_back(guard1);
}

void Engine::move(state::Pawn &pawn, state::Coordinate to) {
    int position = to.getCoordInLine();
    int pawnPosition = attack(to);
    if (board->tiles.at(position).exist && (pawn.getAP() + board->tiles.at(position).getMoveCost()) >= 0) {
        if (pawnPosition == -1) {
            //no attack
            pawn.move(to);
            board->tiles.at(position).effect(pawn);
            pawn.notify();
        } else {
            //attack
            //solving
            if (pawn.attack(board->pawns.at(pawnPosition))) {
                //pawn win
                // attacked step back
                //attacker move
                //board->pawns.at(pawnPosition).move();
                pawn.move(to);
                board->tiles.at(position).effect(pawn);
            }
            //if pawn lose, nothing append (for the moment)
            pawn.notify();
            board->pawns.at(pawnPosition).notify();
        }
    }
}

state::Pawn &Engine::playingPawn() {
    for (int i = 0; i < board->pawns.size(); ++i) {
        if (board->pawns.at(i).isPlaying) {
            return board->pawns[i];
        }
    }
    return board->pawns[0];
}

void Engine::nextTurn() {
    for (int i = 0; i < board->pawns.size(); ++i) {
        if (board->pawns.at(i).isPlaying) {
            board->pawns[i].isPlaying = false;
            if (i + 1 >= board->pawns.size()) {
                board->pawns[0].setAP(1);
                board->pawns[0].isPlaying = true;
            } else {
                board->pawns[i + 1].setAP(1);
                board->pawns[i + 1].isPlaying = true;
            }
            break;
        }
    }
}

std::vector<state::Coordinate> Engine::matrixAv_Tile(state::Pawn &pawn) {
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
        if (board->tiles.at((x - 1) * HEIGHT + y).exist &&
            ap + board->tiles.at((x - 1) * HEIGHT + y).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x - 1, y});
    if (row_up)
        if (board->tiles.at((x + 1) * HEIGHT + y).exist &&
            ap + board->tiles.at((x + 1) * HEIGHT + y).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x + 1, y});
    if (col_down)
        if (board->tiles.at(x * HEIGHT + (y - 1)).exist &&
            ap + board->tiles.at(x * HEIGHT + (y - 1)).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x, y - 1});
    if (col_up)
        if (board->tiles.at(x * HEIGHT + (y + 1)).exist &&
            ap + board->tiles.at(x * HEIGHT + (y + 1)).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x, y + 1});
    if (row_down && col_up)
        if (board->tiles.at((x - 1) * HEIGHT + (y + 1)).exist &&
            ap + board->tiles.at((x - 1) * HEIGHT + (y + 1)).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x - 1, y + 1});
    if (row_up && col_down)
        if (board->tiles.at((x + 1) * HEIGHT + (y - 1)).exist &&
            ap + board->tiles.at((x + 1) * HEIGHT + (y - 1)).getMoveCost() >= 0)
            av_tiles.emplace_back(state::Coordinate{x + 1, y - 1});
    return av_tiles;
}

int Engine::attack(state::Coordinate to) {
    for (int i = 0; i < board->pawns.size(); ++i) {
        if (board->pawns.at(i).getCoordinate() == to) {
            return i;
        }
    }
    return -1;

}