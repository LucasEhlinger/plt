#include "Resources.h"
using namespace ::state;

void Resources::modifyGold(int offset) {
    this->gold += offset;
}

void Resources::modifyMana(int offset) {
    this->mana += offset;
}

void Resources::modifyPrestige(int offset) {
    this->prestige += offset;
}

void Resources::modifyRot(int offset) {
    this->rot += offset;
}