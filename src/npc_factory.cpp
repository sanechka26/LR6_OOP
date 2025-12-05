#include "../include/npc_factory.h"
#include "../include/ork.h"
#include "../include/druid.h"
#include "../include/slaver.h"
#include <stdexcept>
#include <string>
#include <algorithm> 


std::string toUpper(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

NPC* NPCFactory::createNPC(const std::string& type, const std::string& name, double x, double y) {
    std::string upperType = toUpper(type);

    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::invalid_argument("Coordinates must be in range [0, 500]");
    }

    if (upperType == "ORK") {
        return new ORK(name, x, y);
    }
    else if (upperType == "DRUID") {
        return new DRUID(name, x, y);
    }
    else if (upperType == "SLAVER") {
        return new SLAVER(name, x, y);
    }
    else {
        throw std::invalid_argument("Unknown NPC type: " + type);
    }
}