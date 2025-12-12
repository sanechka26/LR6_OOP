#include <gtest/gtest.h>
#include "../include/NPCFactory.h"
#include "../include/NPCContaner.h"

TEST(FactoryTest, ValidNPCCreated) {
    NPCContaner container;
    NPCFactory factory;

    auto* npc = factory.createNPC(container, "ORK", "Grog", 10, 20);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Grog");
    EXPECT_EQ(npc->getType(), "ORK");
    EXPECT_DOUBLE_EQ(npc->getX(), 10);
    EXPECT_DOUBLE_EQ(npc->getY(), 20);
}

TEST(FactoryTest, DuplicateNameThrows) {
    NPCContaner container;
    NPCFactory factory;
    factory.createNPC(container, "ORK", "Grog", 0, 0);

    EXPECT_THROW(
        factory.createNPC(container, "DRUID", "Grog", 0, 0),
        std::invalid_argument
    );
}

TEST(FactoryTest, InvalidCoordsThrow) {
    NPCContaner container;
    NPCFactory factory;

    EXPECT_THROW(
        factory.createNPC(container, "ORK", "Grog", -1, 0),
        std::invalid_argument
    );
    EXPECT_THROW(
        factory.createNPC(container, "ORK", "Grog", 501, 0),
        std::invalid_argument
    );
}