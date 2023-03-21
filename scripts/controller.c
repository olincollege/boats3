/**
 * Handles interaction with the user.
 */

#include "controller.h"
#include "model.h"
#include "view.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int handle_event(SDL_Event event) {
  // WORKING AS INTENDED = 0
  // CHANGE_SPEED = 1
  // CHANGE_COLOR = 2
  // QUIT = 3

  switch (event.type) {
  // if you press a key
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      return 3;
      break;
    case SDLK_SPACE:
      return 1;
      break;
    }
    break;

  // Sometimes it registers ESCAPE without a KEYDOWN.
  case SDL_QUIT:
    return 3;
    break;

  case SDL_MOUSEBUTTONDOWN:
    return 2;
    break;
  }
  return 0;
}
