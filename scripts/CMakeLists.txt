find_library(SDL2 SDL2_image REQUIRED)

add_executable(window main window.c main.c)
target_link_libraries(window SDL2 SDL2_image)
