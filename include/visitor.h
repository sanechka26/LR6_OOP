#pragma once
#include <vector>
#include <memory>

class NPC;

class Visitor {
public:
    virtual void visit(std::vector<NPC*>& npcs) = 0;
    virtual ~Visitor() = default;
};