#pragma once
#include <string>

class NPC;

class NPCFactory {
public:
    static NPC* createNPC(const std::string& type, const std::string& name, double x, double y);
};