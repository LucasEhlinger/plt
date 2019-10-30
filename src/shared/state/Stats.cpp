#include "Stats.h"

using namespace ::state;

Stats::Stats(int combativeness, int vitality, int presenceOfMind, int spirituality) : combativeness(combativeness),
                                                                                      vitality(vitality),
                                                                                      presenceOfMind(presenceOfMind),
                                                                                      spirituality(spirituality) {}

int Stats::getCombativeness() const { return combativeness; }

void Stats::setCombativeness(int combativeness) { this->combativeness = combativeness; }

int Stats::getPresenceOfMind() const { return presenceOfMind; }

void Stats::setPresenceOfMind(int presenceOfMind) { this->presenceOfMind = presenceOfMind; };

int Stats::getSpirituality() const { return spirituality; }

void Stats::setSpirituality(int spirituality) { this->spirituality = spirituality; }

int Stats::getVitality() const { return vitality; }

void Stats::setVitality(int vitality) { this->vitality = vitality; }


bool Stats::operator==(state::Stats &rhs) {
    return vitality == rhs.vitality &&
           spirituality == rhs.spirituality &&
           presenceOfMind == rhs.presenceOfMind &&
           combativeness == rhs.combativeness;
}