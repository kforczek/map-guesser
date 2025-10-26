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

set(Qt6_DIR /home/kuba/Qt/6.9.2/gcc_64/lib/cmake/Qt6)

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

add_executable(map_guesser main.cpp
        src/streetview/token.h
        src/streetview/token.cpp
        src/common/location.h
        src/streetview/streetview.h
        src/streetview/streetview.cpp
)
target_link_libraries(map_guesser PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)

file(COPY ${CMAKE_SOURCE_DIR}/src/streetview/streetview.html DESTINATION ${CMAKE_BINARY_DIR}/res)

# Optional: Print current build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")