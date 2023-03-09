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
  animation cat_animate = {.texture =cat_texture,.frames_loop = {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12},.num_frames=26};
  animation cat_animate1 = {.texture =cat_texture,.frames_loop ={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12},.num_frames=26};
  animation cat_animate2 = {.texture =cat_texture,.frames_loop ={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12},.num_frames=26};
  animation cat_animate3 = {.texture =cat_texture,.frames_loop ={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12},.num_frames=26};
  
  SDL_Texture* explosion_texture = initialize_texture("assets/explosion.png",init.renderer);
  animation explosion0 = {.texture =explosion_texture,.frames_loop ={0,1,2,3,4,5,6,7},.num_frames=8};
  
  
  
  //this is redundant, we only need that first one
  //animation explosion1 = {.texture =explosion_texture,.frames_loop ={0,1,2,3,4,5,6,7},.num_frames=8};
  //animation explosion2 = {.texture =explosion_texture,.frames_loop ={0,1,2,3,4,5,6,7},.num_frames=8};
  //animation explosion3 = {.texture =explosion_texture,.frames_loop ={0,1,2,3,4,5,6,7},.num_frames=8};
  //animation explosion4 = {.texture =explosion_texture,.frames_loop ={0,1,2,3,4,5,6,7},.num_frames=8};
  //animation explosion5 = {.texture =explosion_texture,.frames_loop ={0,1,2,3,4,5,6,7},.num_frames=8};

  //also redundant
  
  //initialize_animation(&explosion1,6,8,1);
  //initialize_animation(&explosion2,6,8,2);
  //initialize_animation(&explosion3,6,8,3);
  //initialize_animation(&explosion4,6,8,4);
  //initialize_animation(&explosion5,6,8,5);

  // not useful anymore
  //animation * explosion_list[10] = {&explosion0,&explosion1,&explosion2,&explosion3,&explosion4,&explosion5};
  
  animation explosion_list[10];
  make_sequential_animation(explosion_list,&explosion0,6,8,6);

  initialize_animation(&explosion0,6,8,0);
  //number of num_rows,num_cols, selected row

  printf("cat initialization\n");

  animation cat_list[10];
  make_sequential_animation(cat_list,&cat_animate,8,12,4);

  initialize_animation(&cat_animate,8,12,0);
  initialize_animation(&cat_animate1,8,12,1);
  initialize_animation(&cat_animate2,8,12,2);
  initialize_animation(&cat_animate3,8,12,3);


  //animation * cat_list[10] = {&cat_animate,&cat_animate1,&cat_animate2,&cat_animate3};


  //SDL_Rect cat_box = {0,0,550,350};
  //numerical arguments: xpos, ypos, scaling value
  SDL_Rect cat_box;
  make_animation_box(&cat_box,&cat_animate,0,0,10);
  SDL_Rect cat_box1;
  make_animation_box(&cat_box1,&cat_animate1,0,350,10);
  SDL_Rect cat_box2;
  make_animation_box(&cat_box2,&cat_animate2,550,0,10);
  SDL_Rect cat_box3;
  make_animation_box(&cat_box3,&cat_animate3,550,350,10);

  SDL_Rect cat_box4;
  make_animation_box(&cat_box4,&cat_animate,1100,350,10);

  SDL_Rect explode_box;
  make_animation_box(&explode_box,&explosion0,1100,0,1);

  //animation * cat_list[10] = {&cat_animate,&cat_animate1,&cat_animate2,&cat_animate3};


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
    //SDL_RenderCopy(init.renderer, cat_texture, NULL, &cat_box);

    //loop_Animation(&boat_animate,init.renderer,&animation_box);

    loop_Animation(&cat_animate,init.renderer,&cat_box);
    loop_Animation(&cat_animate1,init.renderer,&cat_box1);
    loop_Animation(&cat_animate2,init.renderer,&cat_box2);
    loop_Animation(&cat_animate3,init.renderer,&cat_box3);

    //printf("got here 3\n");

    animate_sequential(init.renderer,cat_list,&cat_box4,4);
    //printf("got here 4\n");
    animate_sequential(init.renderer,explosion_list,&explode_box,6);


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
