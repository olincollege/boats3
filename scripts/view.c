/*
Handle's the user's view of the system; displaying background + surfaces
*/

#include "view.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h> /* printf and fprintf */
#include <stdlib.h>

state setup_state() {
  state init;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    (void)fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
  }
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    (void)fprintf(stderr, "Error SDL2_image Initialization-PNG\n");
  }
  if (IMG_Init(IMG_INIT_JPG) == 0) {
    (void)fprintf(stderr, "Error SDL2_image Initialization-JPG\n");
  }

  // Creates a SDL window
  init.window = SDL_CreateWindow(
      "Desktop Pet",           // Title of the SDL window
      SDL_WINDOWPOS_UNDEFINED, // Position x of the window
      SDL_WINDOWPOS_UNDEFINED, // Position y of the window
      WIDTH,                   // Width of the window in pixels
      HEIGHT,                  // Height of the window in pixels
      SDL_WINDOW_BORDERLESS || SDL_WINDOW_MAXIMIZED); // Additional flag(s)

  if (init.window == NULL) {
    (void)fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
  }

  init.renderer = SDL_CreateRenderer(init.window, -1, SDL_RENDERER_ACCELERATED);
  if (init.renderer == NULL) {
    (void)fprintf(stderr, "Error with creating renderer\n");
  }
  init.background = IMG_Load("assets/background.png");
  if (init.background == NULL) {
    (void)fprintf(stderr, "Error with loading image\n");
  }
  init.texture = SDL_CreateTextureFromSurface(init.renderer, init.background);
  if (init.texture == NULL) {
    (void)fprintf(stderr, "Error with creating texture from surface\n");
  }
  SDL_FreeSurface(init.background);

  return init;
}
