#include <gtest/gtest.h>
#include "../include/NPCContaner.h"
#include "../include/ORK.h"

TEST(ContainerTest, AddAndRemove) {
    NPCContaner container;
    ORK* ork = new ORK("Grog", 0, 0);
    
    container.add(ork);
    EXPECT_TRUE(container.hasName("Grog"));
    EXPECT_EQ(container.getAll().size(), 1);

    container.remove("Grog");
    EXPECT_FALSE(container.hasName("Grog"));
    EXPECT_EQ(container.getAll().size(), 0);
}