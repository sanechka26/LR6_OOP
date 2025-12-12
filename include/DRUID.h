#pragma once
 
#include "../include/NPC.h"

class DRUID : public NPC
{
public:
    DRUID(std::string name, double x, double y);
    std::string getType() const override;
    bool canKill(const NPC& other) const override;
};