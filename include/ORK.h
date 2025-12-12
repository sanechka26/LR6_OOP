#pragma once
 
#include "../include/NPC.h"

class ORK : public NPC
{
public:
    ORK(std::string name, double x, double y);
    std::string getType() const override;
    bool canKill(const NPC& other) const override;
};