#include <gtest/gtest.h>
#include "../include/NPCFactory.h"
#include "../include/NPCContaner.h"
#include "../include/SUBJECTS.h"
#include "../include/BattleVisitor.h"
#include "../include/OBSERVER.h"

TEST(BattleTest, TwoORKsKillEachOther) {
    NPCContaner container;
    NPCFactory factory;
    SUBJECTS subject;
    Observer_CMD obs;
    subject.attach(&obs);

    factory.createNPC(container, "ORK", "A", 0, 0);
    factory.createNPC(container, "ORK", "B", 5, 0); // dist = 5

    BATTLEVisitor visitor(10.0, container, subject);
    visitor.startBattle();

    // Оба должны умереть
    EXPECT_EQ(container.getAll().size(), 0);
}

TEST(BattleTest, ORKKillsDruid) {
    NPCContaner container;
    NPCFactory factory;
    SUBJECTS subject;
    Observer_CMD obs;
    subject.attach(&obs);

    factory.createNPC(container, "ORK", "Grog", 0, 0);
    factory.createNPC(container, "DRUID", "Elvin", 5, 0);

    BATTLEVisitor visitor(10.0, container, subject);
    visitor.startBattle();

    auto remaining = container.getAll();
    EXPECT_EQ(remaining.size(), 1);
    EXPECT_EQ(remaining[0]->getName(), "Grog");
}