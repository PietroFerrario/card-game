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
    src/cards/cardInstance.cpp
    src/cards/cardDefinition.cpp
    src/cards/effects/gainArmorEffect.cpp

    src/deck/deckCombat.cpp
    src/deck/deckPlayer.cpp
    
    src/entities/player.cpp
    src/entities/enemies/enemy.cpp  

    src/factories/cardFactory.cpp

    src/game_system/cardmatch.cpp
    src/game_system/game.cpp

    src/ui/iotext.cpp
    src/ui/text.cpp
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

add_executable(deckTest src/tests/deckTest.cpp)
target_link_libraries(deckTest PRIVATE cardgame_core)

add_executable(creatingCardsTest src/tests/creatingCardsTest.cpp)
target_link_libraries(creatingCardsTest PRIVATE cardgame_core)

add_executable(cardMatchTest src/tests/cardMatchTest.cpp)
target_link_libraries(cardMatchTest PRIVATE cardgame_core)