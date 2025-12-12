#pragma once
 
#include "../include/NPC.h"

class SLAVER : public NPC
{
public:
    SLAVER(std::string name, double x, double y);
    std::string getType() const override;
    bool canKill(const NPC& other) const override;
};