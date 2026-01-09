cmake_minimum_required(VERSION 3.24)
project(CardGame VERSION 0.0.1 LANGUAGES CXX)

set(SOURCES 
    src/main.cpp 
    src/game_system/cardmatch.cpp
    src/game_system/player.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
       src)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)