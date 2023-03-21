/*
A simple view for our desktop pet
*/

#pragma once

#include "model.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct initialized_state {
  SDL_Window *window;
  SDL_Texture *texture;
  SDL_Renderer *renderer;
  SDL_Surface *background;
} state;

/**
 * Set up the background of our desktop pet interaction.
 *
 * When called, generate a state object and initialize it
 * with all of the necessary qualities.
 *  *
 * @return the initialized background with all textures
 * and renderings
 */
state setup_state();
