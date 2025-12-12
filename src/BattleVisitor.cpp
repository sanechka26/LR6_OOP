#include "../include/BattleVisitor.h"
#include <math.h>

BATTLEVisitor::BATTLEVisitor(double distanse, NPCContaner& c, SUBJECTS& s) : distance(distance), contaner(c), subj(s) {}

void BATTLEVisitor::startBattle() {
    auto npcs = contaner.getAll();
    if (npcs.size() < 2) {
        return;
    }

    struct KillEvent {
        std::string killerName;
        std::string victimName;
        std::string killerType;
        std::string victimType;
    };
    std::vector<KillEvent> kills;

    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            double dx = npcs[i]->getX() - npcs[j]->getX();
            double dy = npcs[i]->getY() - npcs[j]->getY();
            double dist = std::sqrt(dx*dx + dy*dy);
            std::cout << "Distance between " << npcs[i]->getName() 
                      << " and " << npcs[j]->getName() << ": " << dist << "\n";

            if (npcs[i]->canKill(*npcs[j])) {
                std::cout << "[DEBUG] " << npcs[i]->getName()
                          << " (" << npcs[i]->getType() << ") can kill "
                          << npcs[j]->getName()
                          << " (" << npcs[j]->getType() << ")\n";

                kills.push_back({
                    npcs[i]->getName(), npcs[j]->getName(),
                    npcs[i]->getType(), npcs[j]->getType()
                });
            }
            if (npcs[j]->canKill(*npcs[i])) {
                std::cout << "[DEBUG] " << npcs[j]->getName()
                          << " (" << npcs[j]->getType() << ") can kill "
                          << npcs[i]->getName()
                          << " (" << npcs[i]->getType() << ")\n";

                kills.push_back({
                    npcs[j]->getName(), npcs[i]->getName(),
                    npcs[j]->getType(), npcs[i]->getType()
                });
                break;
            }
        }
    }

    for (const auto& ke : kills) {
        std::string message = ke.killerType + " " + ke.killerName +
                              " убил " + ke.victimType + " " + ke.victimName;
        std::cout << "[LOG] " << message << "\n";
        subj.notifyObservers(message);
        contaner.remove(ke.victimName);
    }
}