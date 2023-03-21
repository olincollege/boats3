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
