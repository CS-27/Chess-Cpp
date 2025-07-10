cmake_minimum_required(VERSION 3.10)

project(ChessGame VERSION 1.0)

# Set Debug by default if not provided
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2 # or latest
)
FetchContent_MakeAvailable(catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

# Add SFML include and lib paths
include_directories("C:/Users/chris/SFML-3.0.0/include")
link_directories("C:/Users/chris/SFML-3.0.0/lib")


file(GLOB_RECURSE SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/game.cpp")

add_executable(chessgame
    src/game.cpp
    ${SOURCES}
)

add_executable(tests
    tests/test_main.cpp
    tests/test_pawn.cpp
    tests/test_board.cpp
    ${SOURCES}   # now without game.cpp
)

# Link SFML
target_link_libraries(chessgame sfml-graphics sfml-window sfml-system)

# Compiler flags
target_compile_options(chessgame PRIVATE -Wall -Wextra)

set_target_properties(chessgame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"  # fallback for single-config generators
)

target_include_directories(tests PRIVATE
    src
    ${catch2_SOURCE_DIR}/src
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain sfml-graphics sfml-window sfml-system)

set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"  # fallback for single-config generators
)

# Windows: remove console window if not debugging
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  target_link_options(chessgame PRIVATE -mwindows)
endif()