#include "../include/SUBJECTS.h"

SUBJECTS& SUBJECTS::attach(OBSERVER* observer)
{
    obs_list.push_back(observer);
    return *this;
};

SUBJECTS& SUBJECTS::detach(OBSERVER* observer)
{
    auto it = std::find(obs_list.begin(), obs_list.end(), observer);
    if (it != obs_list.end()) {
        obs_list.erase(it);
    }
    return *this;
};

void SUBJECTS::notifyObservers(std::string message) noexcept 
{
    for (auto it = obs_list.begin(); it != obs_list.end(); ++it)
    {
        (*it)->update(message);
    }
    
};