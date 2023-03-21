/**
 * A simple view for our desktop pet.
 */

#pragma once

#include "model.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * A structure containing all of the parameters of the screen's background
 * display.
 */
typedef struct initialized_state {
  // A pointer to an SDL Window object.
  SDL_Window *window;
  // A pointer to the image representing the pet, displayed on screen.
  SDL_Texture *texture;
  // A pointer to an SDL Renderer object.
  SDL_Renderer *renderer;
  // A pointer to the image representing the background.
  SDL_Surface *background;
} state;

/**
 * Set up the background of the desktop pet interaction.
 *
 * When called, generate a state object and initialize it
 * with all of the necessary qualities.
 *  *
 * @return the initialized background with all textures and renderings.
 */
state setup_state();
