cmake_minimum_required (VERSION 3.24)
project(final LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(pybind11 REQUIRED)


file(GLOB final Engine/src/*.cpp Engine/src/GameWorld/*.cpp Engine/src/GameWorld/enums/*.cpp)
add_executable(PROG ${final})
include_directories(PROG ./Engine/include)
target_link_libraries(PROG SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer pybind11::embed pybind11::pybind11)


