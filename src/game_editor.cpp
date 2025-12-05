#include "../include/game_editor.h"
#include "../include/npc_factory.h"
#include "../include/visitor.h"
#include "battle_visitor.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

GameEditor::GameEditor() = default;

GameEditor::~GameEditor() {
    for (auto* npc : npcs_) {
        delete npc;
    }
}

void GameEditor::printList() {
    if (npcs_.empty()) {
        std::cout << "No NPCs.\n";
        return;
    }
    std::cout << "\n--- NPC LIST ---\n";
    for (size_t i = 0; i < npcs_.size(); ++i) {
        auto* npc = npcs_[i];
        std::cout << i + 1 << ". " << npc->getType()
                  << " \"" << npc->getName() << "\" at ("
                  << npc->getX() << ", " << npc->getY() << ")\n";
    }
    std::cout << "----------------\n";
}

void GameEditor::addNPC() {
    std::string type, name;
    double x, y;

    std::cout << "Enter type (ORK/DRUID/SLAVER): ";
    std::cin >> type;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter x (0-500): ";
    std::cin >> x;
    std::cout << "Enter y (0-500): ";
    std::cin >> y;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!\n";
        return;
    }

    try {
        NPC* npc = NPCFactory::createNPC(type, name, x, y);
        npcs_.push_back(npc);
        std::cout << "NPC added successfully.\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void GameEditor::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Cannot open file for writing: " << filename << "\n";
        return;
    }

    for (auto* npc : npcs_) {
        file << npc->getType() << "," << npc->getName() << ","
             << npc->getX() << "," << npc->getY() << "\n";
    }
    file.close();
    std::cout << "Saved to " << filename << "\n";
}

void GameEditor::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "File not found: " << filename << "\n";
        return;
    }

    for (auto* npc : npcs_) delete npc;
    npcs_.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
            std::cout << "Invalid line: " << line << "\n";
            continue;
        }

        std::string type = line.substr(0, pos1);
        std::string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string xstr = line.substr(pos2 + 1, pos3 - pos2 - 1);
        std::string ystr = line.substr(pos3 + 1);

        try {
            double x = std::stod(xstr);
            double y = std::stod(ystr);
            NPC* npc = NPCFactory::createNPC(type, name, x, y);
            npcs_.push_back(npc);
        } catch (const std::exception& e) {
            std::cout << "Error parsing line: " << line << " — " << e.what() << "\n";
        }
    }
    file.close();
    std::cout << "Loaded from " << filename << "\n";
}

void GameEditor::startBattle() {
    if (npcs_.size() < 2) {
        std::cout << "Need at least 2 NPCs to battle.\n";
        return;
    }

    double range;
    std::cout << "Enter battle range (e.g., 50.0): ";
    std::cin >> range;

    if (std::cin.fail() || range < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid range!\n";
        return;
    }

    BattleVisitor visitor(range);
    visitor.visit(npcs_);
    std::cout << "Battle finished. Remaining NPCs: " << npcs_.size() << "\n";
}

void GameEditor::run() {
    int choice;
    do {
        std::cout << "\n=== GAME EDITOR ===\n";
        std::cout << "1. Add NPC\n";
        std::cout << "2. Print list\n";
        std::cout << "3. Save to file\n";
        std::cout << "4. Load from file\n";
        std::cout << "5. Start battle\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: addNPC(); break;
            case 2: printList(); break;
            case 3: saveToFile("save.txt"); break;
            case 4: loadFromFile("save.txt"); break;
            case 5: startBattle(); break;
            case 0: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}