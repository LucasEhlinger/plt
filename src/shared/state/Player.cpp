#include "Player.h"
using namespace ::state;

Player::Player(state::Coordinate position, std::string name) : Pawn(position, name){}

void Player::set_number_type (int nb_type) {
    this->number_type = nb_type;
}
