cmake_minimum_required(VERSION 3.30)
project(map_guesser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Optimization flags for Release builds only
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
# Debug flags (these are usually set by default, but can be explicit)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

add_executable(map_guesser main.cpp
        include/google/token.h
        src/google/token.cpp
        include/geo/location.h
        include/google/streetview.h
        src/google/streetview.cpp
        src/geo/location.cpp
        include/google/coverage.h
        src/google/coverage.cpp
        include/game/randomizer.h
        include/db/location_pool.h
        src/game/randomizer.cpp
        include/google/interactive_map.h
        src/google/interactive_map.cpp
        include/google/html_reader.h
        src/google/html_reader.cpp
        include/google/interactive_map_bridge.h
        src/google/interactive_map_bridge.cpp
        include/game/game_window.h
        src/game/game_window.cpp
        src/db/location_pool.cpp
        include/google/distance_map.h
        src/google/distance_map.cpp
        include/google/distance_updater.h
        src/google/distance_map_bridge.cpp
        include/game/pages/street_view.h
        src/game/pages/street_view.cpp
        include/game/pages/round_results.h
        src/game/pages/round_results.cpp
        include/game/results.h
        src/game/results.cpp
)

target_include_directories(map_guesser
        PUBLIC ${CMAKE_SOURCE_DIR}/include
        PRIVATE ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(map_guesser PRIVATE Qt6::Widgets Qt6::WebEngineWidgets curl)

file(COPY ${CMAKE_SOURCE_DIR}/src/google/html/ DESTINATION ${CMAKE_BINARY_DIR}/html)

# Optional: Print current build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")