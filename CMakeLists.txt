cmake_minimum_required(VERSION 3.16)
project(attack_of_the_squares)

set(CMAKE_CXX_STANDARD 20)

add_executable(attack_of_the_squares main.cpp Game.cpp Game.h Enemy.cpp Enemy.h)

add_subdirectory(include/SFML)

target_link_libraries(attack_of_the_squares
        PUBLIC
        sfml-graphics sfml-audio sfml-window sfml-system )

target_include_directories(attack_of_the_squares PRIVATE)
