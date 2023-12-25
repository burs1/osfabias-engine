cmake_minimum_required(VERSION 3.28.1)

# ~ project info
project(
  osfeng
  VERSION 1.0.0
  LANGUAGES CXX
)

# ~ settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# ~ add subdirs
add_subdirectory(src)

# ~ options
option(BUILD_EXAMPLE "Whether or not to build example project" ON)

if (BUILD_EXAMPLE)
  add_subdirectory(example)
endif()
