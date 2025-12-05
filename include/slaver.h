#pragma once
#include "npc.h"

class SLAVER : public NPC {
public:
    SLAVER(const std::string& name, double x, double y);
    std::string getType() const override;
    bool canKill(const NPC& other) const override;
};