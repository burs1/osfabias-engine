# ~ add target
add_library(app app.cpp)

# ~ include directories
target_include_directories(
  app
  PRIVATE ${CMAKE_SOURCE_DIR}/include/osfeng/app
)

# ~ link libs
target_link_libraries(
  app
  PUBLIC window
)
