message(STATUS "Building example")

# ~ project info
project(osfeng_example)

# ~ add building target
add_executable(example main.cpp)

# ~ link libs
target_link_libraries(
  example
  PRIVATE osfeng
)
