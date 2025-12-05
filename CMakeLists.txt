cmake_minimum_required(VERSION 3.14)
project(NPC_Battle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    src/main.cpp
    src/game_editor.cpp
    src/npc_factory.cpp
    src/battle_visitor.cpp
    src/logger.cpp
    src/npc.cpp
    src/ork.cpp
    src/druid.cpp
    src/slaver.cpp
)

add_executable(npc_battle ${SRCS})

target_include_directories(npc_battle PRIVATE ../include)