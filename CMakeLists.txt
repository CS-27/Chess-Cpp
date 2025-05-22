cmake_minimum_required(VERSION 3.10)

project(ChessGame VERSION 1.0)

# Set Debug by default if not provided
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add SFML include and lib paths
include_directories("C:/Users/chris/SFML-3.0.0/include")
link_directories("C:/Users/chris/SFML-3.0.0/lib")

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(chessgame ${SOURCES})

# Link SFML
target_link_libraries(chessgame sfml-graphics sfml-window sfml-system)

# Compiler flags
target_compile_options(chessgame PRIVATE -Wall -Wextra)

set_target_properties(chessgame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"  # fallback for single-config generators
)

# Windows: remove console window if not debugging
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  target_link_options(chessgame PRIVATE -mwindows)
endif()