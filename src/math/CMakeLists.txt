# ~ vars
set(SOURCE_FILES vec2.cpp vec3.cpp matrix4x4.cpp)

# ~ add building target
add_library(math ${SOURCE_FILES})

# ~ link dirs
target_include_directories(
  math
  PRIVATE ${CMAKE_SOURCE_DIR}/include/osfeng/math
)
