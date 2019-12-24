#include <SFML/System.hpp>
#include "Engine.h"
#include "state.h"
#include "ai.h"
#include <queue>
#include <unordered_map>


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
sf::Vector3i evenr_to_cube(state::Coordinate hex);
int offset_distance(state::Coordinate hex_a, state::Coordinate hex_b);
int cube_distance(sf::Vector3i hex_a, sf::Vector3i hex_b);

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

template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
            std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

state::Coordinate Engine::pathfinding(state::Coordinate goal) {
    state::Coordinate start = Engine::playingPawn().getCoordinate();
    int save = Engine::playingPawn().getAP();
    PriorityQueue<int, int> frontier;
    std::vector<state::Coordinate> neighbors;
    std::unordered_map<int, int> came_from;
    std::unordered_map<int, int> cost_so_far;

    frontier.put(start.getCoordInLine(), 0);
    came_from[start.getCoordInLine()] = start.getCoordInLine();
    cost_so_far[start.getCoordInLine()] = 0;

    while(!frontier.empty()) {
        int current = frontier.get();
        state::Coordinate cur_coor{0,0};
        cur_coor.setCoord(current);

        if (current == goal.getCoordInLine())
            break;

        Engine::playingPawn().setCoordinate(cur_coor);
        Engine::playingPawn().setAP(3);
        neighbors = Engine::matrixAv_Tile(Engine::playingPawn());
        for (state::Coordinate next : neighbors) {
            int new_cost = cost_so_far[current] - board->tiles.at(next.getCoordInLine()).getMoveCost();
            if (cost_so_far.find(next.getCoordInLine()) == cost_so_far.end() || new_cost < cost_so_far[next.getCoordInLine()]) {
                cost_so_far[next.getCoordInLine()] = new_cost;
                int priority = new_cost + offset_distance(cur_coor, goal);
                frontier.put(next.getCoordInLine(), priority);
                came_from[next.getCoordInLine()] = current;
            }
        }
    }
    Engine::playingPawn().setCoordinate(start);
    Engine::playingPawn().setAP(save);
    return start;
}

sf::Vector3i evenr_to_cube(state::Coordinate hex) {
    int x = hex.getColumn() - (hex.getRow() + (hex.getRow() & 1)) / 2;
    int z = hex.getRow();
    int y = -x - z;
    return sf::Vector3i{x, y, z};
}

int offset_distance(state::Coordinate hex_a, state::Coordinate hex_b) {
    sf::Vector3i hex_a_c = evenr_to_cube(hex_a);
    sf::Vector3i hex_b_c = evenr_to_cube(hex_b);
    return cube_distance(hex_a_c, hex_b_c);
}

int cube_distance(sf::Vector3i hex_a, sf::Vector3i hex_b) {
    return std::max(std::max(std::abs(hex_a.x - hex_b.x), std::abs(hex_a.y - hex_b.y)), std::abs(hex_a.z - hex_b.z));
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
