/**
 * Main game loop
 *
 */

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "model.h"
#include "view.h"

int main(void) {
  const SDL_Event event;
  /*
   * Initialises the SDL video subsystem (as well as the events subsystem).
   * Returns 0 on success or a negative error code on failure using
   * SDL_GetError().
   */

  // If we set up the state successfully
  init_s = setup_state(init);

  while (!quit) {
    SDL_WaitEvent(&event);

    switch (event.type) {
    // if you press a key
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        printf("got here\n");
        quit = true;
        break;
      }

      // break out of larger SDL_KEYDOWN
      break;

    case SDLK_ESCAPE:
      quit = true;
      break;

    case SDL_QUIT:
      quit = true;
      break;
    }
    SDL_RenderClear(init_s.renderer);
    SDL_RenderCopy(init_s.renderer, init_s.texture, NULL, NULL);
    SDL_RenderPresent(init_s.renderer);
  }

  end_program(init_s.texture, init_s.background, init_s.renderer,
              init_s.window);
  return 0;
}
