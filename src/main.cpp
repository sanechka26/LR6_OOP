#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../include/NPC.h"
#include "../include/DRUID.h"
#include "../include/ORK.h"
#include "../include/SLAVER.h"
#include "../include/NPCContaner.h"
#include "../include/NPCFactory.h"
#include "../include/OBSERVER.h"
#include "../include/SUBJECTS.h"
#include "../include/BattleVisitor.h"

int main() {
    try {
        NPCContaner container;
        NPCFactory factory;
        SUBJECTS subject;

        Observer_CMD consoleObserver;
        Observer_File fileObserver;
        subject.attach(&consoleObserver);
        subject.attach(&fileObserver);

        int choice;
        while (true) {
            std::cout << "\nMenu:\n";
            std::cout << "1. Add NPC\n";
            std::cout << "2. List all NPCs\n";
            std::cout << "3. Start Battle Mode\n";
            std::cout << "4. Save NPCs to file\n";
            std::cout << "5. Load NPCs from file\n";
            std::cout << "0. Exit\n";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }

            switch (choice) {
                case 1: {
                    std::cout << "\n--- Add NPC ---\n";
                    std::cout << "types: ORK, DRUID, SLAVER\n";
                    
                    std::string type, name;
                    double x, y;

                    std::cout << "Type: ";
                    std::cin >> type;
                    for (char& c : type) c = std::toupper(c);

                    std::cout << "Name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);

                    std::cout << "X (0-500): ";
                    if (!(std::cin >> x)) {
                        std::cin.clear(); std::cin.ignore(10000, '\n');
                        std::cout << "X must be a num.\n";
                        continue;
                    }

                    std::cout << "Y (0-500): ";
                    if (!(std::cin >> y)) {
                        std::cin.clear(); std::cin.ignore(10000, '\n');
                        std::cout << "Y must be a num.\n";
                        continue;
                    }

                    try {
                        factory.createNPC(container, type, name, x, y);
                        std::cout << "NPC added: " << type << " \"" << name 
                                  << "\" @ (" << x << ", " << y << ")\n";
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }

                case 2: {
                    std::cout << "\n--- NPC List ---\n";
                    auto all = container.getAll();
                    if (all.empty()) {
                        std::cout << "No NPCs.\n";
                    } else {
                        for (size_t i = 0; i < all.size(); ++i) {
                            std::cout << (i+1) << ". "
                                      << all[i]->getType() << " \""
                                      << all[i]->getName() << "\" @ ("
                                      << all[i]->getX() << ", " << all[i]->getY() << ")\n";
                        }
                    }
                    break;
                }

                case 3: {
                    if (container.getAll().size() < 2) {
                        std::cout << "need 2 NPCs to battle in cont.\n";
                        break;
                    }
                    double dist;
                    std::cout << "Battle radius: ";
                    if (!(std::cin >> dist) || dist < 0) {
                        std::cin.clear(); std::cin.ignore(10000, '\n');
                        std::cout << "Invalid distance.\n";
                        break;
                    }
                    BATTLEVisitor visitor(dist, container, subject);
                    visitor.startBattle();
                    std::cout << "Battle finished. Survivors: " << container.getAll().size() << "\n";
                    break;
                }

                case 4: {
                    std::string filename;
                    std::cout << "\nFilename to save (default: dungeon.txt): ";
                    std::cin.ignore();
                    std::getline(std::cin, filename);
                    if (filename.empty()) filename = "dungeon.txt";

                    if (factory.saveToFile(container, filename)) {
                        std::cout << "Saved to " << filename << "\n";
                    } else {
                        std::cout << "Failed to open file.\n";
                    }
                    break;
                }

                case 5: {
                    std::string filename;
                    std::cout << "\nFilename to load (default: dungeon.txt): ";
                    std::cin.ignore();
                    std::getline(std::cin, filename);
                    if (filename.empty()) filename = "dungeon.txt";

                    if (factory.loadFromFile(container, filename)) {
                        std::cout << "Loaded from " << filename << "\n";
                    } else {
                        std::cout << "File not found or invalid format.\n";
                    }
                    break;
                }

                case 0:
                    return 0;

                default:
                    std::cout << "Invalid choice.\n";
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Critical error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}