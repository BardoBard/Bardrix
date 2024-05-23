cmake_minimum_required(VERSION 3.27)
project(Examples)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(Introduction)
add_subdirectory(Raytracing)