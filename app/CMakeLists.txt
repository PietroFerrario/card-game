cmake_minimum_required(VERSION 3.24)
project(CardGame VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    nlohmann
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann)


add_library(cardgame_core)
target_sources(cardgame_core PRIVATE 
    src/game_system/cardmatch.cpp
    src/game_system/player.cpp
    src/game_system/game.cpp
    src/game_system/iotext.cpp
    src/game_system/text.cpp
    src/card_system/card.cpp
    src/card_system/deckCombat.cpp
    src/card_system/deckPlayer.cpp
    src/card_system/effects/effect.cpp
    )

target_compile_definitions(cardgame_core PUBLIC
    $<$<CONFIG:Debug>:CARDGAME_DEBUG>)

target_include_directories(cardgame_core PUBLIC src)
target_link_libraries(cardgame_core PUBLIC nlohmann_json::nlohmann_json)
target_compile_features(cardgame_core PUBLIC cxx_std_23)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE cardgame_core)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CMAKE_SOURCE_DIR}/data
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/data

)

add_executable(deck_test src/tests/deck_test.cpp)
target_link_libraries(deck_test PRIVATE cardgame_core)