#pragma once

#include "../include/OBSERVER.h"
#include <vector>
#include <algorithm>

class SUBJECTS
{
private:
    std::vector<OBSERVER*> obs_list;
public:
    SUBJECTS() = default;
    ~SUBJECTS() = default;
    SUBJECTS& attach(OBSERVER* observer);
    SUBJECTS& detach(OBSERVER* observer);
    void notifyObservers(std::string message) noexcept;
};
