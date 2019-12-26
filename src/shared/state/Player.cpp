#include "Player.h"
using namespace ::state;

Player::Player(state::Coordinate position, std::string name, bool isHuman) : Pawn(position, name){
    this->isHuman = isHuman;
    this->starting_tile = position;
    AP_max = 3;
}

void Player::set_number_type (int nb_type) {
    this->number_type = nb_type;
}
