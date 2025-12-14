cmake_minimum_required(VERSION 3.10)

project(ChessGame VERSION 1.0)

# Set Debug by default if not provided
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# Add SFML include and lib paths
include_directories("C:/Users/chris/SFML-3.0.0/include")
link_directories("C:/Users/chris/SFML-3.0.0/lib")


file(GLOB_RECURSE SOURCES "src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*/game\\.cpp$")

add_executable(chessgame
    src/game.cpp
    ${SOURCES}
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

add_executable(tests
    tests/test_board.cpp
    tests/test_main.cpp
    ${SOURCES}
)

target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE Catch2::Catch2 sfml-graphics sfml-window sfml-system)

set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"  # fallback for single-config generators
)

if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  target_link_options(chessgame PRIVATE -mwindows)
endif()