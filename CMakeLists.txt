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
        src/google/streetview.h
        src/google/streetview.cpp
        src/geo/point.cpp
        src/google/coverage.h
        src/google/coverage.cpp
        src/app/random_point.cpp
        src/google/interactive_map.h
        src/google/interactive_map.cpp
        src/google/html_reader.h
        src/google/html_reader.cpp
        src/google/interactive_map_bridge.h
        src/google/interactive_map_bridge.cpp
        src/app/main_window.h
        src/app/main_window.cpp
        src/google/distance_map.h
        src/google/distance_map.cpp
        src/google/distance_map_bridge.h
        src/google/distance_map_bridge.cpp
        src/google/polygon_map.h
        src/google/polygon_map.cpp
        src/google/polygon_map_bridge.h
        src/google/polygon_map_bridge.cpp
        src/app/ui/pages/street_view.h
        src/app/ui/pages/street_view.cpp
        src/app/ui/pages/round_results.h
        src/app/ui/pages/round_results.cpp
        src/game/round_results.h
        src/game/results.cpp
        src/app/error_message.h
        src/app/error_message.cpp
        src/app/ui/pages/start.h
        src/app/ui/pages/start.cpp
        src/app/ui/pages/map_editor.h
        src/app/ui/pages/map_editor.cpp
        src/app/ui/widgets/map_editor_top_bar.h
        src/app/ui/widgets/map_editor_top_bar.cpp
        src/geo/region.h
        src/geo/region.cpp
        src/geo/map.h
        src/geo/map.cpp
        src/geo/map_import.cpp
        src/geo/map_export.cpp
        src/util/consumable.h
        src/app/ui/map_file_selector.h
        src/app/ui/map_file_selector.cpp
        src/planar/point.h
        src/planar/map.h
        src/planar/map.cpp
        src/app/ui/pages/game_setup.h
        src/game/params.h
        src/game/session.h
        src/app/ui/widgets/propedit/map_path.h
        src/app/ui/widgets/propedit/base.h
        src/app/ui/widgets/propedit/base.cpp
        src/app/ui/widgets/propedit/map.cpp
        src/app/ui/pages/game_setup.cpp
        src/app/ui/map_file_access.h
        src/app/ui/map_file_access.cpp
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
        src/app/random_point.h
        src/app/ui/widgets/propedit/positive_number.h
        src/app/ui/widgets/propedit/positive_number.cpp
)

target_include_directories(map_guesser
        PUBLIC ${CMAKE_SOURCE_DIR}/include
        PRIVATE ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(map_guesser PRIVATE Qt6::Widgets Qt6::WebEngineWidgets curl)

file(COPY ${CMAKE_SOURCE_DIR}/src/google/html/ DESTINATION ${CMAKE_BINARY_DIR}/html)
file(COPY ${CMAKE_SOURCE_DIR}/src/styles/ DESTINATION ${CMAKE_BINARY_DIR}/styles)

# Optional: Print current build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")