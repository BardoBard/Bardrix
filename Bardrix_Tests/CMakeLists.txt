cmake_minimum_required(VERSION 3.27)
project(Bardrix_Tests VERSION ${BARDRIX_VERSION})

include(FetchContent)
enable_testing()

# Add GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
# End of GoogleTest

# Glob include
file(GLOB_RECURSE SOURCES "*.cpp")

# Add Bardrix
add_executable(${PROJECT_NAME}
        test_main.cpp # Main file for tests
        ${SOURCES})

target_link_libraries(${PROJECT_NAME} Bardrix GTest::gtest)

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Add tests
add_test(NAME Bardrix_GTests COMMAND ${PROJECT_NAME})