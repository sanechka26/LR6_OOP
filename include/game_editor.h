#pragma once
#include <vector>
#include <string>

class NPC;
class Visitor;

class GameEditor {
private:
    std::vector<NPC*> npcs_;

public:
    GameEditor();
    ~GameEditor();

    void run();

private:
    void addNPC();
    void printList();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void startBattle();
};