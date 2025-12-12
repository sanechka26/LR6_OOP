#include "../include/DRUID.h"

DRUID::DRUID(std::string name, double x, double y) : NPC(name, x, y) {}

std::string DRUID::getType() const {
    return "DRUID";
}

bool DRUID::canKill(const NPC& other) const {
    (void)other;
    return false;
}