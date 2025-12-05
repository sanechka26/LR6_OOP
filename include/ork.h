#pragma once
#include "npc.h"

class ORK : public NPC {
public:
    ORK(const std::string& name, double x, double y);
    std::string getType() const override;
    bool canKill(const NPC& other) const override;
};