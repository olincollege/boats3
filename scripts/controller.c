/*
Handles interaction with the user.
*/

#include "controller.h"
#include "model.h"
#include "view.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>

void Handle_Event(bool* quit, SDL_Event event) {

  switch (event.type) {
  // if you press a key
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {

    case SDLK_ESCAPE:
      *quit = true;
      break;
    }
    switch (event.type) {
    // if you press a key
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        printf("got here (Handle_Event)\n");
        *quit = true;
        break;
      }

      // break out of larger SDL_KEYDOWN
      break;

    case SDL_QUIT:
      *quit = true;
      break;
    }
  }
}
