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
        include/geo/point.h
        include/google/streetview.h
        src/google/streetview.cpp
        src/geo/point.cpp
        include/google/coverage.h
        src/google/coverage.cpp
        src/app/random_point.cpp
        include/google/interactive_map.h
        src/google/interactive_map.cpp
        include/google/html_reader.h
        src/google/html_reader.cpp
        include/google/interactive_map_bridge.h
        src/google/interactive_map_bridge.cpp
        include/app/main_window.h
        src/app/main_window.cpp
        include/google/distance_map.h
        src/google/distance_map.cpp
        include/google/distance_map_bridge.h
        src/google/distance_map_bridge.cpp
        include/google/polygon_map.h
        src/google/polygon_map.cpp
        include/google/polygon_map_bridge.h
        src/google/polygon_map_bridge.cpp
        include/app/ui/pages/street_view.h
        src/app/ui/pages/street_view.cpp
        include/app/ui/pages/round_results.h
        src/app/ui/pages/round_results.cpp
        include/app/results.h
        src/app/results.cpp
        include/app/error_message.h
        src/app/error_message.cpp
        include/app/ui/pages/start.h
        src/app/ui/pages/start.cpp
        include/app/ui/pages/map_editor.h
        src/app/ui/pages/map_editor.cpp
        include/app/ui/widgets/map_editor_top_bar.h
        src/app/ui/widgets/map_editor_top_bar.cpp
        include/geo/region.h
        src/geo/region.cpp
        include/geo/map.h
        src/geo/map.cpp
        src/geo/map_import.cpp
        src/geo/map_export.cpp
        include/util/consumable.h
        include/app/ui/map_file_selector.h
        src/app/ui/map_file_selector.cpp
        include/planar/point.h
        include/planar/map.h
        src/planar/map.cpp
        include/app/ui/pages/game_setup.h
        include/game/params.h
        include/game/session.h
        include/app/ui/widgets/propedit/map_path.h
        include/app/ui/widgets/propedit/base.h
        src/app/ui/widgets/propedit/base.cpp
        src/app/ui/widgets/propedit/map_path.cpp
        src/app/ui/pages/game_setup.cpp
        include/app/ui/map_file_access.h
        src/app/ui/map_file_access.cpp
        src/game/session.cpp
        include/lambert/projection.h
        src/lambert/projection.cpp
        include/geo/consts.h
        include/planar/region.h
        src/planar/region.cpp
        src/planar/point.cpp
        include/planar/triangle.h
        src/planar/triangle.cpp
        include/planar/triangulation.h
        src/planar/triangulation.cpp
        include/app/random_point.h
)

target_include_directories(map_guesser
        PUBLIC ${CMAKE_SOURCE_DIR}/include
        PRIVATE ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(map_guesser PRIVATE Qt6::Widgets Qt6::WebEngineWidgets curl)

file(COPY ${CMAKE_SOURCE_DIR}/src/google/html/ DESTINATION ${CMAKE_BINARY_DIR}/html)

# Optional: Print current build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")