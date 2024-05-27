cmake_minimum_required(VERSION 3.27)
project(Bardrix)
set(BARDRIX_VERSION 0.2.2)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(BARDRIX_BUILD_TESTS "Build test programs" OFF)

# Add Bardrix library
add_subdirectory(Bardrix)

# Add BardrixTest if Bardrix is the project
if (BARDRIX_BUILD_TESTS OR
        PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    add_subdirectory(Bardrix_Tests)
endif ()
