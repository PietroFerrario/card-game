cmake_minimum_required(VERSION 3.24)
project(CardGame VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    nlohmann
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE 
    src/main.cpp 
    src/game_system/cardmatch.cpp
    src/game_system/player.cpp
    src/game_system/game.cpp
    src/game_system/iotext.cpp
    src/game_system/text.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PRIVATE
       src
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CMAKE_SOURCE_DIR}/data
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/data

)