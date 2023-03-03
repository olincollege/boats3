/*
Handles interaction with the user.
*/

#include "controller.h"
#include "model.h"
#include "view.h"

void Handle_Event(SDL_Event event) {

  switch (event.type) {
  // if you press a key
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {

    case SDLK_ESCAPE:
      quit = true;
      break;
    }
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

    case SDL_QUIT:
      quit = true;
      break;
    }
  }
}
