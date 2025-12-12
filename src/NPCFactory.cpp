#include "../include/NPCFactory.h"
#include "../include/ORK.h"
#include "../include/SLAVER.h"
#include "../include/DRUID.h"
#include <fstream>
#include <sstream>

NPC* NPCFactory::createNPC(NPCContaner& dungeon, std::string type, std::string name, double x, double y) {
    if (0 > x || x > 500 || 0 > y || y > 500)
    {
        throw std::invalid_argument("x and y should be in [0; 500]");
    }
    if (dungeon.hasName(name))
    {
        throw std::invalid_argument("Name already exists");
    }

    NPC* npc = nullptr;

    if (type == "ORK")
    {
        npc = new ORK(name, x, y);
    }
    else if (type == "DRUID")
    {
        npc = new DRUID(name, x, y);
    }
    else if (type == "SLAVER")
    {
        npc = new SLAVER(name, x, y);
    }
    else
    {
        throw std::invalid_argument("Invalid type of hero");
    }

    dungeon.add(npc);
    return npc;
}

bool NPCFactory::saveToFile(const NPCContaner& container, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    auto npcs = container.getAll();
    for (const auto& npc : npcs) {
        file << npc->getType() << ","
             << npc->getName() << ","
             << npc->getX() << ","
             << npc->getY() << "\n";
    }
    return true;
}

bool NPCFactory::loadFromFile(NPCContaner& container, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string type, name;
        double x, y;

        if (!std::getline(iss, type, ',') ||
            !std::getline(iss, name, ',') ||
            !(iss >> x) || !(iss.ignore()) || !(iss >> y)) {
            continue;
        }

        try {
            createNPC(container, type, name, x, y);
        } catch (...) {
        }
    }
    return true;
}