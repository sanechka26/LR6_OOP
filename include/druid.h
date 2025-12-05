#pragma once
#include "npc.h"

class DRUID : public NPC {
public:
    DRUID(const std::string& name, double x, double y);
    std::string getType() const override;
    bool canKill(const NPC& other) const override;
};