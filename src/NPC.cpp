#include "../include/NPC.h"

NPC::NPC(std::string name, double x, double y) : name(name), x(x), y(y) {}

std::string NPC::getName() const {
    return name;
}

double NPC::getX() const { return x; };
double NPC::getY() const { return y; };