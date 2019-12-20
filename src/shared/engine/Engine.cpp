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

    state::Player player2{state::Coordinate{12, 6}, "player 2", false};
    player2.number_type = 2;

    state::King king{state::Coordinate{6, 6}};
    king.setAP(0);
    king.isPlaying = true;

    state::Guard guard1{state::Coordinate{8, 10}, "guard 1"};

    this->board->pawns.emplace_back(king);
    this->board->pawns.emplace_back(guard1);
    this->board->pawns.emplace_back(player1);
    this->board->pawns.emplace_back(player2);
}

void sim_attack(state::Pawn playing, state::Coordinate goal, bool aim, int modifier = 0);

void Engine::move(state::Pawn &pawn, state::Coordinate to) {
    int position = to.getCoordInLine();
    int pawnPosition = attack(to);
    std::array<int, 2> result;
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
            int mountain = 0;
            if (board->tiles.at(position).number_type == 3)
                mountain = 1;
            result = pawn.attack(defender, this->board->day, mountain);
            pawn.modifyLP(std::max(result[1], 0) * (-1));
            defender.modifyLP(std::max(result[0], 0) * (-1));

            // attacker wins, defender steps back and attacker moves (draw is considered win)
            if (result[0] >= result[1]) {
                defender.setAP(2);
                defender.move(state::Coordinate{defender.getCoordinate().getRow() + vec.x,
                                                defender.getCoordinate().getColumn() + vec.y});
                pawn.move(to);
                board->tiles.at(position).effect(pawn);
            }
                // attacker loses, attacker still uses AP but no moves are made
            else
                pawn.modifyAP(board->tiles.at(to.getCoordInLine()).getMoveCost());
            pawn.notify();
            defender.notify();
        }
    }

}

state::Pawn &Engine::playingPawn() {
    return board->playingPawn();
}

void Engine::nextTurn() {
    board->nextTurn();
}

std::vector<state::Coordinate> Engine::matrixAv_Tile(state::Pawn &pawn) {
    return board->matrixAv_Tile(pawn);
}

state::Coordinate Engine::pathfinding(state::Coordinate coord) {

    state::Pawn playing = Engine::playingPawn();
    std::vector<state::Coordinate> av_moves = board->matrixAv_Tile(playing);
    int row = playing.getCoordinate().getRow();
    int col = playing.getCoordinate().getColumn();
    int vert = -1;
    int hori = -1;

    //si coord est un départ (start : 7) ou un chateau (Castle : 8)
    if (board->tiles.at(coord.getCoordInLine()).number_type == 7 ||
        board->tiles.at(coord.getCoordInLine()).number_type == 8)
        return ai::Random::action(av_moves);

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
        return ai::Random::action(av_moves);
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
    return ai::Random::action(av_moves);
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
    return pathfinding(ai::Heuristic::action(*board));
}
