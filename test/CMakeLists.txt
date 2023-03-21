# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

find_library(SDL2 SDL2_image m REQUIRED)

add_executable(test_model test_model.c)

target_link_libraries(test_model
  PRIVATE model
  PRIVATE SDL2 SDL2_image m
  PUBLIC ${CRITERION}
)

add_test(
  NAME test_model
  COMMAND test_model ${CRITERION_FLAGS}
)
