#pragma once

#include "../include/NPC.h"

class NPCContaner
{
private:
    std::vector<NPC*> pull;
public:
    NPCContaner() = default;
    virtual ~NPCContaner() = default;

    NPCContaner& add(NPC* other);
    NPCContaner& remove(std::string name);
    bool hasName(std::string name) const;
    std::vector<NPC*> getAll() const;
};