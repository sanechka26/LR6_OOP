#include "../include/druid.h"

DRUID::DRUID(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

std::string DRUID::getType() const {
    return "DRUID";
}

bool DRUID::canKill(const NPC& other) const {
    return false;
}