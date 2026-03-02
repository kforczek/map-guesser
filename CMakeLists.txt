cmake_minimum_required(VERSION 3.30)
project(map_guesser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

# --- geo ---
add_library(geo STATIC
        src/geo/point.h
        src/geo/point.cpp
        src/geo/region.h
        src/geo/region.cpp
        src/geo/map.h
        src/geo/map.cpp
        src/geo/consts.h
)
target_include_directories(geo PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_features(geo PUBLIC cxx_std_23)

# --- planar ---
add_library(planar STATIC
        src/planar/point.h
        src/planar/point.cpp
        src/planar/map.h
        src/planar/map.cpp
        src/planar/region.h
        src/planar/region.cpp
        src/planar/triangle.h
        src/planar/triangle.cpp
        src/planar/triangulation.h
        src/planar/triangulation.cpp
)
target_include_directories(planar PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_features(planar PUBLIC cxx_std_23)

# --- lambert ---
add_library(lambert STATIC
        src/lambert/projection.h
        src/lambert/projection.cpp
)
target_include_directories(lambert PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_features(lambert PUBLIC cxx_std_23)
target_link_libraries(lambert PUBLIC geo planar)

# --- google ---
add_library(google STATIC
        src/google/token.h
        src/google/token.cpp
        src/google/coverage.h
        src/google/coverage.cpp
)
target_include_directories(google PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_features(google PUBLIC cxx_std_23)
target_link_libraries(google PUBLIC geo curl)

# --- game ---
add_library(game STATIC
        src/util/consumable.h
        src/game/defs.h
        src/game/params.h
        src/game/random_point.h
        src/game/random_point.cpp
        src/game/round_results.h
        src/game/round_results.cpp
        src/game/session.h
        src/game/session.cpp
        src/game/game.h
        src/game/game.cpp
        src/game/mode/engine.h
        src/game/mode/engine_base.h
        src/game/mode/engine_base.cpp
        src/game/mode/engine_fixed_rounds.h
        src/game/mode/engine_fixed_rounds.cpp
        src/game/mode/observer.h
)
target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_features(game PUBLIC cxx_std_23)
target_link_libraries(game PUBLIC geo planar lambert google)

add_library(user STATIC
        src/user/dir.h
        src/user/dir.cpp
        src/user/api_usage.h
        src/user/api_usage.cpp
)
target_include_directories(user PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_features(user PUBLIC cxx_std_23)

# --- ui ---
add_library(ui STATIC
        src/ui/bridge/commands.h
        src/ui/bridge/connection.h
        src/ui/bridge/connection.cpp
        src/ui/google/streetview.h
        src/ui/google/streetview.cpp
        src/ui/google/interactive_map.h
        src/ui/google/interactive_map.cpp
        src/ui/google/interactive_map_bridge.h
        src/ui/google/interactive_map_bridge.cpp
        src/ui/google/html_reader.h
        src/ui/google/html_reader.cpp
        src/ui/google/distance_map.h
        src/ui/google/distance_map.cpp
        src/ui/google/distance_map_bridge.h
        src/ui/google/distance_map_bridge.cpp
        src/ui/google/polygon_map.h
        src/ui/google/polygon_map.cpp
        src/ui/google/polygon_map_bridge.h
        src/ui/google/polygon_map_bridge.cpp
        src/ui/main_window.h
        src/ui/main_window.cpp
        src/ui/pages/gameplay.h
        src/ui/pages/gameplay.cpp
        src/ui/pages/round_results.h
        src/ui/pages/round_results.cpp
        src/ui/pages/start.h
        src/ui/pages/start.cpp
        src/ui/pages/map_editor.h
        src/ui/pages/map_editor.cpp
        src/ui/pages/game_setup.h
        src/ui/pages/game_setup.cpp
        src/ui/pages/ghost_walk.h
        src/ui/pages/ghost_walk.cpp
        src/ui/pages/summary.h
        src/ui/pages/summary.cpp
        src/ui/widgets/map_editor_top_bar.h
        src/ui/widgets/map_editor_top_bar.cpp
        src/ui/widgets/propedit.h
        src/ui/widgets/propedit.cpp
        src/ui/mapfile/selector.h
        src/ui/mapfile/selector.cpp
        src/ui/mapfile/access.h
        src/ui/mapfile/access.cpp
        src/ui/google/streetview_bridge.h
        src/ui/google/streetview_bridge.cpp
)
target_include_directories(ui PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_features(ui PUBLIC cxx_std_23)
target_link_libraries(ui PUBLIC Qt6::Widgets PRIVATE Qt6::WebEngineWidgets user)

# --- executable ---
add_executable(map_guesser main.cpp)
target_link_libraries(map_guesser PRIVATE game ui user)

# TODO: compile content to constexpr strings
file(COPY ${CMAKE_SOURCE_DIR}/src/ui/google/html/ DESTINATION ${CMAKE_BINARY_DIR}/html)
file(COPY ${CMAKE_SOURCE_DIR}/src/ui/styles/ DESTINATION ${CMAKE_BINARY_DIR}/styles)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
