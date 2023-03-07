SET(GCC_COVERAGE_COMPILE_FLAGS "-lm -lSDL2 -lSDL2_image")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
find_library(SDL2 SDL2_image m REQUIRED)

add_library(controller controller.c controller.h)
add_library(view view.c view.h)
add_library(model model.c model.h)

add_executable(window window.c)
add_executable(main main.c)
target_link_libraries(window model SDL2 SDL2_image m)
target_link_libraries(main model SDL2 SDL2_image m)
