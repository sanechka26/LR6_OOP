#pragma once

#include "../include/NPC.h"
#include "../include/NPCContaner.h"

class NPCFactory
{
public:
    NPC* createNPC(NPCContaner& dungeon, std::string type, std::string name, double x, double y);

    bool saveToFile(const NPCContaner& container, const std::string& filename);
    bool loadFromFile(NPCContaner& container, const std::string& filename);
};

