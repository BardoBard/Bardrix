cmake_minimum_required(VERSION 3.27)
project(Bardrix VERSION ${BARDRIX_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Include header files
include_directories(include)

# Collect source files
file(GLOB SOURCES "src/**/*.cpp")

# Create library
add_library(Bardrix ${SOURCES})

# Include directories in the target
target_include_directories(Bardrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set library version
set_target_properties(Bardrix PROPERTIES VERSION ${PROJECT_VERSION})
