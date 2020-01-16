#include <algorithm>
#include "Resources.h"

using namespace ::state;

Resources::Resources(int gold, int mana, int prestige, int rot) : gold(gold), mana(mana), prestige(prestige),
                                                                  rot(rot) {}
void Resources::modifyGold(int offset) {
    this->gold = std::max(this->gold + offset, 0);
}

void Resources::modifyMana(int offset) {
    this->mana = std::max(this->mana + offset, 0);
}

void Resources::modifyPrestige(int offset) {
    this->prestige = std::max(this->prestige + offset, 0);
}

void Resources::modifyRot(int offset) {
    this->rot = std::max(this->rot + offset, 0);
}

bool Resources::operator==(state::Resources &rhs) {
    return rot == rhs.rot &&
           mana == rhs.mana &&
           prestige == rhs.prestige &&
           gold == rhs.gold;
}