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

    state::Player player3{state::Coordinate{0, 12}, "player 3", true};
    player3.number_type = 3;

    state::Player player4{state::Coordinate{12, 0}, "player 4", false};
    player4.number_type = 0;

    state::King king{state::Coordinate{6, 6}};
    king.setAP(king.AP_max);
    king.isPlaying = true;

    state::Guard guard1{state::Coordinate{8, 10}, "guard 1", false};

    state::Guard guard2{state::Coordinate{5, 6}, "guard 2", true};

    state::Bane bane1{state::Coordinate{8, 7}, "bane 1"};

    this->board->pawns.emplace_back(king);
    this->board->pawns.emplace_back(guard1);
    this->board->pawns.emplace_back(guard2);
    this->board->pawns.emplace_back(bane1);
    this->board->pawns.emplace_back(player1);
    this->board->pawns.emplace_back(player2);
    this->board->pawns.emplace_back(player3);
    this->board->pawns.emplace_back(player4);
}

std::vector<int> Engine::move(state::Coordinate to) {
    std::vector<int> deaths;
    bool att_d = false;
    bool def_d = false;
    int position = to.getCoordInLine();
    int pawnPosition = attack(to);
    std::array<int, 2> result;

    if (board->tiles.at(position).exist &&
        (this->playingPawn().getAP() + board->tiles.at(position).getMoveCost()) >= 0) {
        if (pawnPosition == -1) {
            //no attack
            this->playingPawn().move(to);
            board->tiles.at(position).effect(this->playingPawn());
            if (this->playingPawn().getLP() <= 0)
                death(this->playingPawn());
            this->playingPawn().notify();
        } else {
            // attack solving
            sf::Vector2i vec{to.getRow() - this->playingPawn().getCoordinate().getRow(),
                             to.getColumn() - this->playingPawn().getCoordinate().getColumn()};
            int mountain = 0;
            if (board->tiles.at(position).number_type == 3)
                mountain = 1;
            result = this->playingPawn().attack(board->pawns.at(pawnPosition), this->board->day, mountain);
            this->playingPawn().modifyLP(std::max(result[1], 0) * (-1));
            board->pawns.at(pawnPosition).modifyLP(std::max(result[0], 0) * (-1));

            // check if someone died during the conflict
            if (this->playingPawn().getLP() <= 0) {
                if (board->pawns.at(pawnPosition).getLP() <= 0)
                    if (this->playingPawn().number_type - 4 >= 0)
                        this->playingPawn().modifyResources(0, 0, 1, 0);
                death(this->playingPawn());
                for (int i = 0; i < board->pawns.size(); ++i)
                    if (board->pawns.at(i).isPlaying) {
                        deaths.emplace_back(i);
                        break;
                    }
                att_d = true;
                if (board->pawns.at(pawnPosition).number_type - 4 >= 0)
                    board->pawns.at(pawnPosition).modifyResources(0, 0, 1, 0);
            }
            else {
                // attacker is still alive and wins, attacker moves (draw is considered win)
                if (result[0] >= result[1]) {
                    this->playingPawn().move(to);
                    board->tiles.at(position).effect(this->playingPawn());
                }
                else
                    this->playingPawn().modifyAP(board->tiles.at(position).getMoveCost());
            }
            if (board->pawns.at(pawnPosition).getLP() <= 0) {
                death(board->pawns.at(pawnPosition));
                deaths.emplace_back(pawnPosition);
                def_d = true;
                if (board->pawns.at(pawnPosition).number_type - 4 >= 0)
                    board->pawns.at(pawnPosition).modifyResources(0, 0, 1, 0);
            }
            else
                // attacker wins and is still alive, board->pawns.at(pawnPosition) steps back (gets affected by the tile effect) and attacker moves (draw is considered win)
                if (result[0] >= result[1] && !att_d) {
                    // this needs to be better handled, they can't always step back (edges or castle)
                    board->pawns.at(pawnPosition).move(
                            state::Coordinate{board->pawns.at(pawnPosition).getCoordinate().getRow() + vec.x,
                                              board->pawns.at(pawnPosition).getCoordinate().getColumn() + vec.y});
                    board->tiles.at(state::Coordinate{board->pawns.at(pawnPosition).getCoordinate().getRow() + vec.x,
                                                      board->pawns.at(pawnPosition).getCoordinate().getColumn() +
                                                      vec.y}.getCoordInLine());
                }

            // check if someone died after the movement
            if (this->playingPawn().getLP() <= 0 && !att_d) {
                death(this->playingPawn());
                for (int i = 0; i < board->pawns.size(); ++i)
                    if (board->pawns.at(i).isPlaying && (board->pawns.at(i).number_type == 5 || board->pawns.at(i).number_type == 6)) {
                        deaths.emplace_back(i);
                        break;
                    }
            }
            if (board->pawns.at(pawnPosition).getLP() <= 0 && !def_d) {
                death(board->pawns.at(pawnPosition));
                deaths.emplace_back(pawnPosition);
            }

            this->playingPawn().notify();
            board->pawns.at(pawnPosition).notify();
        }
    }
    return deaths;
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

std::vector<state::Coordinate> Engine::pathfinding(state::Coordinate goal) {
    state::Coordinate start = Engine::playingPawn().getCoordinate();
    int save = Engine::playingPawn().getAP();
    PriorityQueue<int, int> frontier;           // PriorityQueue<Coordinate, int> first member goes through comparisons
    std::vector<state::Coordinate> neighbors;
    std::unordered_map<int, int> came_from;     // unordered_map<Coordinate, Coordinate>
    std::unordered_map<int, int> cost_so_far;   // unordered_map<Coordinate, int>
    /*
     * unordered_map needs a Hash function,
     * we would have to make our own for the Coordinate class when there's an existing one for the int type.
     * Since we already have all the functions to swiftly go from Coordinate to int and back, I'd rather use int here.
     */

    frontier.put(start.getCoordInLine(), 0);
    came_from[start.getCoordInLine()] = start.getCoordInLine();
    cost_so_far[start.getCoordInLine()] = 0;

    while (!frontier.empty()) {
        int current = frontier.get();
        state::Coordinate cur_coor{0, 0};
        cur_coor.setCoord(current);

        if (current == goal.getCoordInLine())
            break;

        Engine::playingPawn().setCoordinate(cur_coor);
        Engine::playingPawn().setAP(3);
        neighbors = Engine::matrixAv_Tile(Engine::playingPawn());
        for (state::Coordinate next : neighbors) {
            int new_cost = cost_so_far[current] - board->tiles.at(next.getCoordInLine()).getMoveCost();
            if (cost_so_far.find(next.getCoordInLine()) == cost_so_far.end() ||
                new_cost < cost_so_far[next.getCoordInLine()]) {
                cost_so_far[next.getCoordInLine()] = new_cost;
                int priority = new_cost + cur_coor.distance(goal);
                frontier.put(next.getCoordInLine(), priority);
                came_from[next.getCoordInLine()] = current;
            }
        }
    }
    Engine::playingPawn().setCoordinate(start);
    Engine::playingPawn().setAP(save);
    std::vector<state::Coordinate> path;
    state::Coordinate current = goal;
    while (current.getCoordInLine() != start.getCoordInLine()) {
        path.push_back(current);
        current.setCoord(came_from[current.getCoordInLine()]);
    }
    return path;
}

int Engine::attack(state::Coordinate to) {
    for (int i = 0; i < board->pawns.size(); ++i) {
        if (board->pawns.at(i).getCoordinate() == to) {
            return i;
        }
    }
    return -1;
}

std::vector<state::Coordinate> Engine::AI_finale() {
    return pathfinding(ai::Heuristic::action(*board));
}

std::vector<state::Coordinate> Engine::guard_behaviour() {
    return pathfinding(ai::AI_Guard::action(*board));
}

std::vector<state::Coordinate> Engine::bane_behaviour() {
    return pathfinding(ai::AI_Bane::action(*board));
}

void Engine::death(state::Pawn &pawn) {
    if (playingPawn() == pawn)
        nextTurn();
    if (pawn.number_type == 5 || pawn.number_type == 6)
        for (int i = 0; i < board->pawns.size(); ++i)
            if (board->pawns.at(i) == pawn) {
                board->pawns.erase(board->pawns.begin() + i);
                break;
            }
    else if (pawn.number_type != 4) {
        pawn.modifyResources(0, 0, -1, 0);
        pawn.to_the_pit();
    }
    pawn.notify();
}
