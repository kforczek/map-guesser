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
        src/game/main_window.h
        src/game/main_window.cpp
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
        src/game/results.cpp
        src/game/error_message.h
        src/game/error_message.cpp
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
        src/ui/map_file_selector.h
        src/ui/map_file_selector.cpp
        src/planar/point.h
        src/planar/map.h
        src/planar/map.cpp
        src/ui/pages/game_setup.h
        src/game/params.h
        src/game/session.h
        src/ui/widgets/propedit/map.h
        src/ui/widgets/propedit/base.h
        src/ui/widgets/propedit/base.cpp
        src/ui/widgets/propedit/map.cpp
        src/ui/pages/game_setup.cpp
        src/ui/map_file_access.h
        src/ui/map_file_access.cpp
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
        src/ui/widgets/propedit/positive_number.h
        src/ui/widgets/propedit/positive_number.cpp
        src/ui/widgets/start_page_bottom_bar.h
        src/ui/widgets/start_page_bottom_bar.cpp
)

target_include_directories(map_guesser
        PUBLIC ${CMAKE_SOURCE_DIR}/include
        PRIVATE ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(map_guesser PRIVATE Qt6::Widgets Qt6::WebEngineWidgets curl)

file(COPY ${CMAKE_SOURCE_DIR}/src/ui/google/html/ DESTINATION ${CMAKE_BINARY_DIR}/html)
file(COPY ${CMAKE_SOURCE_DIR}/src/styles/ DESTINATION ${CMAKE_BINARY_DIR}/styles)

# Optional: Print current build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")