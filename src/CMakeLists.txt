# ~ add subdirs
add_subdirectory(window)

# ~ add target
add_library(osfeng null.cpp)

# ~ include dirs
target_include_directories(
  osfeng
  PUBLIC ../include/osfeng
)

# ~ link libraries
target_link_libraries(
  osfeng
  PUBLIC window
)
