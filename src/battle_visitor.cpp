#include "../include/visitor.h"
#include "../include/npc.h"
#include "../include/observer.h"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

extern Observer* getConsoleLogger();
extern Observer* getFileLogger();

class BattleVisitor : public Visitor {
private:
    double range_;

public:
    explicit BattleVisitor(double range) : range_(range) {}

    double distance(const NPC& a, const NPC& b) const {
        double dx = a.getX() - b.getX();
        double dy = a.getY() - b.getY();
        return std::sqrt(dx * dx + dy * dy);
    }

    void visit(std::vector<NPC*>& npcs) override {
        std::vector<bool> alive(npcs.size(), true);
        Observer* console = getConsoleLogger();
        Observer* filelog = getFileLogger();

        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!alive[i]) continue;
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!alive[j]) continue;

                NPC* a = npcs[i];
                NPC* b = npcs[j];

                if (distance(*a, *b) <= range_) {
                    bool aKillsB = a->canKill(*b);
                    bool bKillsA = b->canKill(*a);

                    if (aKillsB && !bKillsA) {
                        std::string msg = a->getName() + " (" + a->getType() + ") killed " + b->getName() + " (" + b->getType() + ")";
                        console->update(msg);
                        filelog->update(msg);
                        alive[j] = false;
                    }
                    else if (bKillsA && !aKillsB) {
                        std::string msg = b->getName() + " (" + b->getType() + ") killed " + a->getName() + " (" + a->getType() + ")";
                        console->update(msg);
                        filelog->update(msg);
                        alive[i] = false;
                    }
                    else if (aKillsB && bKillsA) {
                        std::string msg = "Mutual destruction: " + a->getName() + " and " + b->getName() + " killed each other";
                        console->update(msg);
                        filelog->update(msg);
                        alive[i] = false;
                        alive[j] = false;
                    }
                }
            }
        }

        for (int i = static_cast<int>(npcs.size()) - 1; i >= 0; --i) {
            if (!alive[i]) {
                delete npcs[i];
                npcs.erase(npcs.begin() + i);
            }
        }
    }
};