cmake_minimum_required(VERSION 3.29)
project(NumGuess)

set(CMAKE_CXX_STANDARD 23)

# ---- Dependencies ----

include(cmake/get_cpm.cmake)

CPMAddPackage("gh:raysan5/raylib#5.5")
CPMAddPackage(
        NAME raygui
        GITHUB_REPOSITORY drasmart/raygui
        GIT_TAG master
        SOURCE_SUBDIR projects/CMake)

# ---- Executable ----

message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/Game
        ${PROJECT_SOURCE_DIR}/src/UI
)

file(GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Game/*.cpp
        ${PROJECT_SOURCE_DIR}/src/UI/*.cpp
)
message(STATUS "SRC_FILES = ${SRC_FILES}")
add_executable(NumGuess ${SRC_FILES})

target_link_libraries(NumGuess raylib raygui)
