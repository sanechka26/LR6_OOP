#include <gtest/gtest.h>
#include "../include/NPC.h"
#include "../include/ORK.h"
#include "../include/DRUID.h"
#include "../include/SLAVER.h"

TEST(NPCTest, ORKCanKillEveryone) {
    ORK ork("Grog", 0, 0);
    DRUID druid("Elvin", 0, 0);
    ORK ork2("Zug", 0, 0);
    SLAVER slaver("Torg", 0, 0);

    EXPECT_TRUE(ork.canKill(druid));
    EXPECT_TRUE(ork.canKill(ork2));
    EXPECT_TRUE(ork.canKill(slaver));
}

TEST(NPCTest, DRUIDKillsNoOne) {
    DRUID druid("Elvin", 0, 0);
    ORK ork("Grog", 0, 0);
    SLAVER slaver("Torg", 0, 0);

    EXPECT_FALSE(druid.canKill(ork));
    EXPECT_FALSE(druid.canKill(slaver));
    EXPECT_FALSE(druid.canKill(druid));
}

TEST(NPCTest, SLAVERKillsOnlyDruids) {
    SLAVER slaver("Torg", 0, 0);
    DRUID druid("Elvin", 0, 0);
    ORK ork("Grog", 0, 0);

    EXPECT_TRUE(slaver.canKill(druid));
    EXPECT_FALSE(slaver.canKill(ork));
    EXPECT_FALSE(slaver.canKill(slaver));
}