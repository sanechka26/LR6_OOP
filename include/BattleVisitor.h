#pragma once

#include "../include/NPCContaner.h"
#include "../include/SUBJECTS.h"

class BATTLEVisitor
{
private:
    double distance;
    NPCContaner& contaner;
    SUBJECTS& subj;
public:
    BATTLEVisitor(double distanse, NPCContaner& c, SUBJECTS& s);
    virtual ~BATTLEVisitor() = default;

    void startBattle();
};
