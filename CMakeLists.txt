cmake_minimum_required(VERSION 3.28)
project(C_GAME)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(C_GAME main.cpp
        Background.cpp
        Background.h
        Menu.h
        Menu.cpp
        Game.h
        Game.cpp
        Options.h
        Options.cpp
)
target_link_libraries(C_GAME sfml-graphics)