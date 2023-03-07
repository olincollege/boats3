/**
 * Main game loop
 *
 */

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//math seems to require the -lm flag
#include "controller.h"
#include "model.h"
#include "view.h"

state init;

state setup_state(state init) {
  /*
   * Initialises the SDL video subsystem (as well as the events subsystem).
   * Returns 0 on success or a negative error code on failure using
   * SDL_GetError().
   */

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    // return 1;
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    printf("Error SDL2_image Initialization-PNG\n");
    // return 2;
  }
  if (IMG_Init(IMG_INIT_JPG) == 0) {
    printf("Error SDL2_image Initialization-JPG\n");
    // return 2;
  }
  // Creates a SDL window
  init.window = SDL_CreateWindow(
      "SDL Example",           /* Title of the SDL window */
      SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
      SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
      WIDTH,                   /* Width of the window in pixels */
      HEIGHT,                  /* Height of the window in pixels */
      SDL_WINDOW_BORDERLESS || SDL_WINDOW_MAXIMIZED); /* Additional flag(s) */

  // Checks if window has been created; if not, exits program
  // if (init.window == NULL) {
  //   fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
  //   return 3;
  // }

  init.renderer = SDL_CreateRenderer(init.window, -1, SDL_RENDERER_ACCELERATED);
  // if (init.renderer == NULL) {
  //   printf("renderer error\n");
  //   return 4;
  // }

  // if (SDL_RenderSetLogicalSize(init.renderer, WIDTH, HEIGHT) != 0) {
  //   printf("resolution setting error\n");
  //   printf("%s\n", SDL_GetError());
  //   return 5;
  // }

  init.background = IMG_Load("assets/background.png");
  // if (init.background == NULL) {
  //   printf("error loading image\n");
  //   return 6;
  // }

  init.texture = SDL_CreateTextureFromSurface(init.renderer, init.background);
  // if (init.texture == NULL) {
  //   printf("error creating texture\n");
  //   return 7;
  // }

  fprintf(stdout, "window initialized\n");
  return init;
}

int main(void) {

  

  const SDL_Event event;
  

  // Initialize our window.
  init = setup_state(init);

  //SDL_Surface *boat_img = IMG_Load("assets/boat.png");
  //SDL_Texture *boat_texture = SDL_CreateTextureFromSurface(init.renderer, boat_img);

  SDL_Texture *boat_texture = initialize_texture("assets/boat.png",init.renderer);

  animation boat_animate = {.texture =boat_texture,.frames_loop ={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5},.num_frames=30};
  //number of num_rows,num_cols, selected row
  initialize_animation(&boat_animate,2,6,1);

  SDL_Rect animation_box = {500,500,550,350};

  //SDL_Surface *cat_img = IMG_Load("assets/catsheet_1.jpg");
  //SDL_Texture *cat_texture = SDL_CreateTextureFromSurface(init.renderer, cat_img);

  SDL_Texture* cat_texture = initialize_texture("assets/catsheet_1.jpg",init.renderer);
  animation cat_animate = {.texture =cat_texture,.frames_loop ={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2},.num_frames=15};
  //number of num_rows,num_cols, selected row
  initialize_animation(&cat_animate,8,12,1);

  SDL_Rect cat_box = {0,0,550,350};




  
  while (!quit) {
    //check the time of this update cycle
    Uint64 time_start = SDL_GetPerformanceCounter();

    //poll event, contents of if need to be in a function, if statement is important
    if (SDL_PollEvent(&event)){

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
    }

    //rendering cycle
    SDL_RenderClear(init.renderer);
    SDL_RenderCopy(init.renderer, init.texture, NULL, NULL);
    SDL_RenderCopy(init.renderer, cat_texture, NULL, &cat_box);

    loop_Animation(&boat_animate,init.renderer,&animation_box);


    SDL_RenderPresent(init.renderer);

    //put this in a function
    Uint64 time_end = SDL_GetPerformanceCounter();
    //find elapse time
    float elapsed_time = (time_end -time_start)/(float)SDL_GetPerformanceFrequency() * 1000.0f;

    //cap fps at 60
    SDL_Delay(floor(16.666f - elapsed_time));
  }

  end_program(init.texture, init.background, init.renderer, init.window);
  return 0;
}
