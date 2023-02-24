/**
 * String utilities similar to functions offered in Python.
 */
#pragma once

#include <stdlib.h>
#include <SDL2/SDL_image.h>


/**
 * Runs the cleanup commands when exiting the program.
 *
 * @param texture An SDL_Texture created from the SDL_Surface object
 * @param image An SDL_Surface representing the image object
 * @param renderer A renderer object
 * @param window An SDL_Window representing the popup window.
 */
void end_program(SDL_Texture *texture, SDL_Surface *image, SDL_Renderer *renderer, SDL_Window *window);
