#pragma once
#include <string>

class NPC {
protected:
    std::string name;
    double x, y;

public:
    NPC(const std::string& name, double x, double y);
    virtual ~NPC();

    double getX() const { return x; }
    double getY() const { return y; }
    std::string getName() const { return name; }

    virtual std::string getType() const = 0;
    virtual bool canKill(const NPC& other) const = 0;
};