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
        src/google/token.h
        src/google/token.cpp
        src/geo/point.h
        src/ui/google/streetview.h
        src/ui/google/streetview.cpp
        src/geo/point.cpp
        src/google/coverage.h
        src/google/coverage.cpp
        src/game/random_point.cpp
        src/ui/google/interactive_map.h
        src/ui/google/interactive_map.cpp
        src/ui/google/html_reader.h
        src/ui/google/html_reader.cpp
        src/ui/google/interactive_map_bridge.h
        src/ui/google/interactive_map_bridge.cpp
        src/ui/main_window.h
        src/ui/main_window.cpp
        src/ui/google/distance_map.h
        src/ui/google/distance_map.cpp
        src/ui/google/distance_map_bridge.h
        src/ui/google/distance_map_bridge.cpp
        src/ui/google/polygon_map.h
        src/ui/google/polygon_map.cpp
        src/ui/google/polygon_map_bridge.h
        src/ui/google/polygon_map_bridge.cpp
        src/ui/pages/street_view.h
        src/ui/pages/street_view.cpp
        src/ui/pages/round_results.h
        src/ui/pages/round_results.cpp
        src/game/round_results.h
        src/game/round_results.cpp
        src/ui/pages/start.h
        src/ui/pages/start.cpp
        src/ui/pages/map_editor.h
        src/ui/pages/map_editor.cpp
        src/ui/widgets/map_editor_top_bar.h
        src/ui/widgets/map_editor_top_bar.cpp
        src/geo/region.h
        src/geo/region.cpp
        src/geo/map.h
        src/geo/map.cpp
        src/geo/map_import.cpp
        src/geo/map_export.cpp
        src/util/consumable.h
        src/ui/utils/map_file_selector.h
        src/ui/utils/map_file_selector.cpp
        src/planar/point.h
        src/planar/map.h
        src/planar/map.cpp
        src/ui/pages/game_setup.h
        src/game/params.h
        src/game/session.h
        src/ui/widgets/propedit.h
        src/ui/widgets/propedit.cpp
        src/ui/pages/game_setup.cpp
        src/ui/utils/map_file_access.h
        src/ui/utils/map_file_access.cpp
        src/game/session.cpp
        src/lambert/projection.h
        src/lambert/projection.cpp
        src/geo/consts.h
        src/planar/region.h
        src/planar/region.cpp
        src/planar/point.cpp
        src/planar/triangle.h
        src/planar/triangle.cpp
        src/planar/triangulation.h
        src/planar/triangulation.cpp
        src/game/random_point.h
        src/game/mode/engine.h
        src/game/game.h
        src/game/mode/engine_base.h
        src/game/mode/engine_fixed_rounds.h
        src/game/mode/engine_fixed_rounds.cpp
        src/game/game.cpp
        src/ui/controller.h
        src/ui/controller.cpp
        src/ui/commands.h
        src/game/mode/engine_base.cpp
        src/game/mode/observer.h
        src/game/defs.h
)

target_include_directories(map_guesser PRIVATE ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(map_guesser PRIVATE Qt6::Widgets Qt6::WebEngineWidgets curl)

# TODO: compile content to constexpr strings
file(COPY ${CMAKE_SOURCE_DIR}/src/ui/google/html/ DESTINATION ${CMAKE_BINARY_DIR}/html)
file(COPY ${CMAKE_SOURCE_DIR}/src/ui/styles/ DESTINATION ${CMAKE_BINARY_DIR}/styles)

# Optional: Print current build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")