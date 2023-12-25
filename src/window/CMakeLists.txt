# ~ vars
set(SOURCE_FILES window.cpp input.cpp sprite.cpp)

# ~ find packages
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

# ~ add building target
add_library(window ${SOURCE_FILES})

# ~ link dirs
target_include_directories(
  window
  PRIVATE ${CMAKE_SOURCE_DIR}/include/osfeng/window
)

# ~ link libs
target_link_libraries(
  window
  PUBLIC SDL2::SDL2
  PUBLIC SDL2_ttf::SDL2_ttf
  PUBLIC SDL2_image::SDL2_image
)
