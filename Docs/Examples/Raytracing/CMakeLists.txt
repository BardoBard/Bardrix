cmake_minimum_required(VERSION 3.27)
project(Raytracing)

include(FetchContent) # Include the FetchContent module

# Clone the Bardrix library
FetchContent_Declare(
        Bardrix
        GIT_REPOSITORY https://github.com/bardobard/Bardrix.git
        GIT_TAG v0.4.2
)

FetchContent_MakeAvailable(Bardrix)

# Add your project files
add_executable(${PROJECT_NAME} main.cpp window.cpp)

# Add bardrix library
target_link_libraries(${PROJECT_NAME} Bardrix)