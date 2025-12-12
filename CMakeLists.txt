cmake_minimum_required(VERSION 3.14)
project(DungeonEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/NPC.cpp
    src/DRUID.cpp
    src/ORK.cpp
    src/SLAVER.cpp
    src/NPCFactory.cpp
    src/NPCContaner.cpp
    src/SUBJECTS.cpp
    src/BattleVisitor.cpp
)

set(HEADERS
    include/NPC.h
    include/DRUID.h
    include/ORK.h
    include/SLAVER.h
    include/NPCFactory.h
    include/NPCContaner.h
    include/SUBJECTS.h
    include/BattleVisitor.h
    include/OBSERVER.h
)

add_executable(dungeon_editor src/main.cpp ${SOURCES} ${HEADERS})
target_include_directories(dungeon_editor PRIVATE include)
add_custom_command(TARGET dungeon_editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/logs
)

find_package(GTest REQUIRED)

add_library(dungeon_core STATIC ${SOURCES})
target_include_directories(dungeon_core PUBLIC include)

enable_testing()

add_executable(runTests
    tests/test_NPC.cpp
    tests/test_Factory.cpp
    tests/test_Container.cpp
    tests/test_Battle.cpp
    tests/test_Observer.cpp
)
target_link_libraries(runTests dungeon_core GTest::gtest GTest::gtest_main)
target_include_directories(runTests PRIVATE include)

add_test(NAME AllTests COMMAND runTests)