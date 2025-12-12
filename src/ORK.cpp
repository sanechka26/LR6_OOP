#include "../include/ORK.h"

ORK::ORK(std::string name, double x, double y) : NPC(name, x, y) {}

std::string ORK::getType() const {
    return "ORK";
}

bool ORK::canKill(const NPC& other) const {
    (void)other;
    return true;
}