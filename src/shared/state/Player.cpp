#include "Player.h"
using namespace ::state;

Player::Player(state::Coordinate position, std::string name, bool isHuman) : Pawn(position, name){
    this->isHuman = isHuman;
    this->starting_tile = position;
    AP_max = 3;

    stats = Stats(4, 5, 0, 0);

    lifePoints = stats.getVitality();
}

void Player::set_number_type (int nb_type) {
    this->number_type = nb_type;
}
