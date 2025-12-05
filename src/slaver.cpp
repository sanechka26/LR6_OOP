#include "../include/slaver.h"

SLAVER::SLAVER(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

std::string SLAVER::getType() const {
    return "SLAVER";
}

bool SLAVER::canKill(const NPC& other) const {
    return other.getType() == "DRUID";
}