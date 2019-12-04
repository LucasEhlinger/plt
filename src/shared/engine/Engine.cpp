#include <SFML/System.hpp>
#include "Engine.h"
#include "state.h"
#include "ai.h"


#define HEIGHT  13
#define WIDTH   13

using namespace engine;
using namespace ai;

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

void sim_attack(state::Pawn playing, state::Coordinate goal, bool aim, int modifier = 0);

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
            state::Pawn defender = board->pawns.at(pawnPosition);
            sf::Vector2i vec = {to.getRow() - pawn.getCoordinate().getRow(),
                                to.getColumn() - pawn.getCoordinate().getColumn()};
            if (pawn.attack(defender, this->board->day)) {
                //pawn win
                // attacked step back
                //attacker move
                defender.move(state::Coordinate{defender.getCoordinate().getRow() + vec.x,
                                                defender.getCoordinate().getColumn() + vec.y});
                pawn.move(to);
                board->tiles.at(position).effect(pawn);
            }
            //if pawn loses, nothing happens (for the moment)
            pawn.notify();
            defender.notify();
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

state::Coordinate Engine::pathfinding() {
    state::Coordinate coord = {8, 6};

    state::Pawn playing = Engine::playingPawn();
    std::vector<state::Coordinate> av_moves = matrixAv_Tile(playing);
    int row = playing.getCoordinate().getRow();
    int col = playing.getCoordinate().getColumn();
    int vert = -1;
    int hori = -1;

    if (board->tiles.at(coord.getRow() * HEIGHT + coord.getColumn()).number_type == 7 &&
        board->tiles.at(coord.getRow() * HEIGHT + coord.getColumn()).number_type == 8)
        return Ai::AI_rand(av_moves);
    if (playing.getCoordinate().getRow() - coord.getRow() < 0)
        vert = 1;
    else if (playing.getCoordinate().getRow() - coord.getRow() == 0)
        vert = 0;
    if (playing.getCoordinate().getColumn() - coord.getColumn() < 0)
        hori = 1;
    else if (playing.getCoordinate().getColumn() - coord.getColumn() == 0)
        hori = 0;

    if (vert == 1 && hori == 1)
        for (int i = 0; i < av_moves.size(); ++i)
            if (av_moves[i] == state::Coordinate{row, col + 1} || av_moves[i] == state::Coordinate{row + 1, col})
                return av_moves[i];
    if (vert == 1 && hori == 0)
        for (int i = 0; i < av_moves.size(); ++i)
            if (av_moves[i] == state::Coordinate{row + 1, col - 1} || av_moves[i] == state::Coordinate{row + 1, col})
                return av_moves[i];
    if (vert == 1 && hori == -1)
        for (int i = 0; i < av_moves.size(); ++i)
            if (av_moves[i] == state::Coordinate{row, col - 1} || av_moves[i] == state::Coordinate{row + 1, col - 1})
                return av_moves[i];
    if (vert == 0 && hori == 1)
        for (int i = 0; i < av_moves.size(); ++i)
            if (av_moves[i] == state::Coordinate{row, col + 1})
                return av_moves[i];
    if (vert == 0 && hori == 0)
        return Ai::AI_rand(av_moves);
    if (vert == 0 && hori == -1)
        for (int i = 0; i < av_moves.size(); ++i)
            if (av_moves[i] == state::Coordinate{row, col - 1})
                return av_moves[i];
    if (vert == -1 && hori == 1)
        for (int i = 0; i < av_moves.size(); ++i)
            if (av_moves[i] == state::Coordinate{row, col + 1} || av_moves[i] == state::Coordinate{row - 1, col + 1})
                return av_moves[i];
    if (vert == -1 && hori == 0)
        for (int i = 0; i < av_moves.size(); ++i)
            if (av_moves[i] == state::Coordinate{row - 1, col + 1} || av_moves[i] == state::Coordinate{row - 1, col})
                return av_moves[i];
    if (vert == -1 && hori == -1)
        for (int i = 0; i < av_moves.size(); ++i)
            if (av_moves[i] == state::Coordinate{row, col - 1} || av_moves[i] == state::Coordinate{row - 1, col})
                return av_moves[i];
    return Ai::AI_rand(av_moves);
}


int Engine::attack(state::Coordinate to) {
    for (int i = 0; i < board->pawns.size(); ++i) {
        if (board->pawns.at(i).getCoordinate() == to) {
            return i;
        }
    }
    return -1;
}

state::Coordinate Engine::AI_finale() {
    state::Pawn playing = Engine::playingPawn();
    state::Coordinate current_coord = playing.getCoordinate();

    bool kill_king, kill_king_q, kill_prestige, kill_prestige_q = false;

    sim_attack(playing, state::Coordinate{6, 6}, kill_king);
    sim_attack(playing, state::Coordinate{6, 6}, kill_king_q, 1);
    bool prestige_win = false;
    state::Coordinate goal{0, 0};
    for (int i = 0; i < board->pawns.size(); ++i)
        if (board->pawns.at(i).getResources().prestige - playing.getResources().prestige < 2 &&
            playing.getResources().prestige < board->pawns.at(i).getResources().prestige) {
            prestige_win = true;
            goal = board->pawns.at(i).getCoordinate();
        }
    if (prestige_win) {
        sim_attack(playing, goal, kill_prestige);
        sim_attack(playing, goal, kill_prestige_q, 1);
    }

    if (kill_king)
        return state::Coordinate{6, 6};
    else if (kill_king_q || kill_prestige_q)
        return Ai::AI_rand(Engine::matrixAv_Tile(playing));
    else if (kill_prestige)
        return goal;
    else
        return Ai::AI_rand(Engine::matrixAv_Tile(playing));
}

void sim_attack(state::Pawn playing, state::Coordinate goal, bool aim, int modifier) {
    int ratio = 0;
    playing.modifyStats(modifier, 0, 0, 0);
    for (int i = 100; --i;) {
        playing.move(goal);
        if (playing.getCoordinate() == goal)
            ++ratio;
    }
    if (ratio > 70)
        aim = true;
}