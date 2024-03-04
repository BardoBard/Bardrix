cmake_minimum_required(VERSION 3.27)
project(Bardrix)

option(BARDRIX_BUILD_TESTS "Build test programs" OFF)
set(BARDRIX_VERSION 0.0.1)

# Add Bardrix library
add_subdirectory(Bardrix)

# Add BardrixTest if BARDRIX_BUILD_TESTS is set
if (BARDRIX_BUILD_TESTS)
    add_subdirectory(Bardrix_Tests)
endif()