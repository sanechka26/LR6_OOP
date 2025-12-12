#pragma once

#include <iostream>
#include <string>
#include <vector>

class NPC
{
private:
    std::string name;
    double x;
    double y;
public:
    NPC(std::string name, double x, double y);
    virtual ~NPC() = default;

    virtual bool canKill(const NPC& other) const = 0;
    virtual std::string getType() const = 0;
    std::string getName() const;
    double getX() const ;
    double getY() const ;
};

