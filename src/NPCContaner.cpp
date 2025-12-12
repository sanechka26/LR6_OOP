#include "../include/NPCContaner.h"

NPCContaner& NPCContaner::add(NPC* other) {
    if (other == nullptr) 
    {
        throw std::invalid_argument("NPC pointer is null");
    }
    pull.push_back(other);
    return *this;
}

NPCContaner& NPCContaner::remove(std::string name) {
    for (auto it = pull.begin(); it != pull.end(); ++it)
    {
        if ((*it)->getName() == name)
        {
            delete *it;
            pull.erase(it);
            break;
        }
    }
    return *this;
}

bool NPCContaner::hasName(std::string name) const {
    for (const auto& i : pull)
    {
        if (i->getName() == name)
        {
            return true;
        }
    }
    return false;
}

std::vector<NPC*> NPCContaner::getAll() const {
    return pull;
}