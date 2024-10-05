cmake_minimum_required(VERSION 3.29)
project(A_star)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 20)

add_executable(A_star main.cpp
        Grid.cpp
        Grid.h
        GameCharacter.cpp
        GameCharacter.h)

target_link_libraries(A_star sfml-graphics)