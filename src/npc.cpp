#include "../include/npc.h"

NPC::NPC(const std::string& name, double x, double y)
    : name(name), x(x), y(y) {}

NPC::~NPC() = default;