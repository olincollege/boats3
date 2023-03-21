/*
Handles interaction with the user.
*/

#include "controller.h"
#include "model.h"
#include "view.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int handle_event(SDL_Event event) {

  // QUIT = 0
  // CHANGE_SPEED = 1
  // CHANGE_COLOR = 2

  switch (event.type) {
  // if you press a key
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      return 0;
      break;
    case SDLK_SPACE:
      return 1;
      break;
    }
    break;

  // Sometimes it registers ESCAPE without a KEYDOWN
  case SDLK_ESCAPE || SDL_QUIT:
    return 0;
    break;

  case SDL_MOUSEBUTTONDOWN:
    return 2;
    break;
  }
  puts("Yikes! An error occurred");
  return 0;
}
