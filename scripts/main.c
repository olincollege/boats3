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

  // ? change this to rely on the initialize_texture function?
  // ? if not, then make sure to free surface
  init.background = IMG_Load("assets/background.png");
  if (init.background == NULL) {
    printf("error loading image\n");
    // return 6;
  }

  init.texture = SDL_CreateTextureFromSurface(init.renderer, init.background);
  // if (init.texture == NULL) {
  //   printf("error creating texture\n");
  //   return 7;
  // }
  SDL_FreeSurface(init.background);

  fprintf(stdout, "window initialized\n");
  return init;
}



int main(void) {
  bool quit = false;
  SDL_Event event;

  // Initialize our window.
  init = setup_state(init);

  SDL_Texture *boat_texture = initialize_texture("assets/boat.png", init.renderer);

  animation boat_animate = {.texture =boat_texture,.frames_loop ={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5},.num_frames=30};
  //number of num_rows,num_cols, selected row
  initialize_animation(&boat_animate,2,6,1);

  // SDL_Rect animation_box = {500,500,550,350};

  //SDL_Surface *cat_img = IMG_Load("assets/catsheet_1.jpg");
  //SDL_Texture *cat_texture = SDL_CreateTextureFromSurface(init.renderer, cat_img);

  SDL_Texture* cat_texture = initialize_texture("assets/catsheet_1.jpg",init.renderer);
  animation cat_animate = {.texture =cat_texture,.frames_loop ={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12},.num_frames=34};
  animation cat_animate1 = {.texture =cat_texture,.frames_loop ={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12},.num_frames=34};
  animation cat_animate2 = {.texture =cat_texture,.frames_loop ={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12},.num_frames=34};
  animation cat_animate3 = {.texture =cat_texture,.frames_loop ={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12},.num_frames=34};
  //number of num_rows,num_cols, selected row

  printf("cat initialization\n");
  initialize_animation(&cat_animate,8,12,0);
  initialize_animation(&cat_animate1,8,12,1);
  initialize_animation(&cat_animate2,8,12,2);
  initialize_animation(&cat_animate3,8,12,3);

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


  SDL_Rect dstrect = {50, 50, SPRITE_WIDTH, SPRITE_HEIGHT}; // sets the desired size/pos of the sprite

  int movement_counter = 0; // spaces out movement commands to look smoother
  int direction = 0; // afaik declaring it once and just changing the value is faster
  int prev = 0;
  int cycle = 0;  // used for my manual pseudo-lerping implementation
  int speed = rand() % 5 + 1;  // an int from 1-10. higher # = higher speed

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
      
      case SDLK_SPACE:
        speed = rand() % 10 + 1;
        printf("Changing speed to %i\n", speed);

      case SDL_QUIT:
        quit = true;
        break;
      }
    }

    movement_counter++;
    if (movement_counter % (200000/SMOOTHNESS) == 0) {
      cycle++;
      if (cycle == SMOOTHNESS) {
        // only update random num if the sprite has pseudo-lerped to another spot
        direction = generate_random(0, 5, &prev);
        cycle = 0;
      }
      move_random_direction(direction, &dstrect, speed, &prev);

      SDL_RenderClear(init.renderer);
      SDL_RenderCopy(init.renderer, init.texture, NULL, NULL);
      SDL_RenderCopy(init.renderer, boat_texture, NULL, &dstrect);
    }
    // randomly change speed
    if (rand() % 70000000 == 0) {
      speed = rand() % 10 + 1;
      printf("Changing speed to %i\n", speed);
    }

    //SDL_RenderCopy(init.renderer, cat_texture, NULL, &cat_box);

    //loop_Animation(&boat_animate,init.renderer,&animation_box);

    loop_Animation(&cat_animate,init.renderer,&cat_box);
    loop_Animation(&cat_animate1,init.renderer,&cat_box1);
    loop_Animation(&cat_animate2,init.renderer,&cat_box2);
    loop_Animation(&cat_animate3,init.renderer,&cat_box3);


    SDL_RenderPresent(init.renderer);

    //put this in a function
    Uint64 time_end = SDL_GetPerformanceCounter();
    //find elapse time
    float elapsed_time = (time_end -time_start)/(float)SDL_GetPerformanceFrequency() * 1000.0f;

    //cap fps at 60
    SDL_Delay(floor(16.666f - elapsed_time));
  }

  end_program(init.texture, boat_texture, init.renderer, init.window);
  return 0;
}
