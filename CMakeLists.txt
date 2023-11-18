cmake_minimum_required(VERSION 3.0)
project(BlackjackGame)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Set the include directories
include_directories(include)

# Add the executable for test_deck
add_executable(test_deck
    tests/test_deck.cpp
    include/deck.hpp
    include/deck.inl
)

# Link the test_deck executable with gtest, gtest_main, and pthread
target_link_libraries(test_deck ${GTEST_BOTH_LIBRARIES} pthread)

# Add the executable for test_dealer
add_executable(test_dealer
    tests/test_dealer.cpp
    include/dealer.hpp
    include/dealer.inl
    include/deck.hpp
    include/deck.inl
)

# Link the test_dealer executable with gtest, gtest_main, and pthread
target_link_libraries(test_dealer ${GTEST_BOTH_LIBRARIES} pthread)

# Add the tests to CTest
enable_testing()
add_test(NAME TestDeck COMMAND test_deck)
add_test(NAME TestDealer COMMAND test_dealer)
