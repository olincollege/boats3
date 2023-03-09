/**
 * Main game loop
 */

#include "controller.h"
#include "model.h"
#include "view.h"
#include <SDL2/SDL_image.h>
#include <math.h> //math seems to require the -lm flag
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

state init;

state setup_state(state init) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
  }
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    printf("Error SDL2_image Initialization-PNG\n");
  }
  if (IMG_Init(IMG_INIT_JPG) == 0) {
    printf("Error SDL2_image Initialization-JPG\n");
  }

  // Creates a SDL window
  init.window = SDL_CreateWindow(
      "SDL Example",           // Title of the SDL window
      SDL_WINDOWPOS_UNDEFINED, // Position x of the window
      SDL_WINDOWPOS_UNDEFINED, // Position y of the window
      WIDTH,                   // Width of the window in pixels
      HEIGHT,                  // Height of the window in pixels
      SDL_WINDOW_BORDERLESS || SDL_WINDOW_MAXIMIZED); // Additional flag(s)

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
  init.background = IMG_Load("assets/background.png");
  if (init.background == NULL) {
    printf("error loading image\n");
  }

  init.texture = SDL_CreateTextureFromSurface(init.renderer, init.background);
  // if (init.texture == NULL) {
  //   printf("error creating texture\n");
  // }
  SDL_FreeSurface(init.background);

  return init;
}

int main(void) {
  bool quit = false;
  SDL_Event event;

  // Initialize our window.
  init = setup_state(init);

  SDL_Texture* cat_texture = initialize_texture("assets/catsheet_1.jpg", init.renderer);

  const int number_frames = 26;
  // int sprint_all[30] =
  // {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,11,11}; int
  // sprint_gray[30] = {0,0,1,1,2,2,1,1,0,0,1,1,2,2,1,1,0,0,1,1,2,2,1,1,0,0};
  // int run_gray[30] = {0,0,0,0,1,1,1,1,2,2,2,2,1,1,1,1,0,0,0,0,1,1,1,1,1,1};
  int walk_gray[30] = {0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1};
  int walk_white[30] = {3,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,5,4,4,4,4,4,4};
  int walk_black[30] = {6,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,8,7,7,7,7,7,7};
  int walk_orange[30] = {9,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,11,10,10,10,10,10,10};
  animation cat_animate = {
    .texture = cat_texture,
    .frames_loop = &walk_orange,
    .num_frames = number_frames};
  animation cat_animate1 = cat_animate;
  animation cat_animate2 = cat_animate;
  animation cat_animate3 = cat_animate;

  const int cat_sheet_rows = 8;
  const int cat_sheet_cols = 12;
  initialize_animation(&cat_animate, cat_sheet_rows, cat_sheet_cols, 0);
  initialize_animation(&cat_animate1, cat_sheet_rows, cat_sheet_cols, 1);
  initialize_animation(&cat_animate2, cat_sheet_rows, cat_sheet_cols, 2);
  initialize_animation(&cat_animate3, cat_sheet_rows, cat_sheet_cols, 3);

  const float cat_box_scale = 3.0;
  SDL_Rect cat_box;
  make_animation_box(&cat_box, &cat_animate, 0, 0, cat_box_scale);
  SDL_Rect cat_box1;
  make_animation_box(&cat_box1, &cat_animate1, 0, SPRITE_HEIGHT, cat_box_scale);
  SDL_Rect cat_box2;
  make_animation_box(&cat_box2, &cat_animate2, SPRITE_WIDTH, 0, cat_box_scale);
  SDL_Rect cat_box3;
  make_animation_box(&cat_box3, &cat_animate3, SPRITE_WIDTH, SPRITE_HEIGHT,
                     cat_box_scale);

  int direction = 0;
  int prev = 0;  // represents the previous direction the sprite moved
  int cycle = 0;  // used for my manual pseudo-lerping implementation
  int speed = 2;  // an int from 1-10. higher # = higher speed

  while (!quit) {
    // check the time of this update cycle
    Uint64 time_start = SDL_GetPerformanceCounter();

    // poll event, contents of if need to be in a function, if statement is
    // important
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      // if you press a key
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          quit = true;
          break;

        case SDLK_SPACE:
          speed = rand() % 10 + 1;
          printf("Manually changing speed to %i\n", speed);
          break;
        }

        // break out of larger SDL_KEYDOWN
        break;

      case SDLK_ESCAPE:
      case SDL_QUIT:
        quit = true;
        break;
      
      case SDL_MOUSEBUTTONDOWN:
          // idk why but commenting out the print statement causes stuff to break. boo.
          printf("Clicked mouse\n");
          SDL_Point mousePosition;
          // Mouse click coords from event handler
          mousePosition.x = event.motion.x; 
          mousePosition.y = event.motion.y;

          if (SDL_PointInRect(&mousePosition, &cat_box)) {
              // printf("Clicked on the sprite\n");

              // int walk_white[30] = {3,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,5,4,4,4,4,4,4};

              // printf(cat_animate.frames_loop);

              if ((cat_animate.frames_loop) == &walk_orange) {
                cat_animate.frames_loop = &walk_black;
                cat_animate1.frames_loop = &walk_black;
                cat_animate2.frames_loop = &walk_black;
                cat_animate3.frames_loop = &walk_black;
              } else {
                cat_animate.frames_loop = &walk_orange;
                cat_animate1.frames_loop = &walk_orange;
                cat_animate2.frames_loop = &walk_orange;
                cat_animate3.frames_loop = &walk_orange;
              }
              //   initialize_animation(&cat_animate, cat_sheet_rows, cat_sheet_cols, 0);
              //   initialize_animation(&cat_animate1, cat_sheet_rows, cat_sheet_cols, 1);
              //   initialize_animation(&cat_animate2, cat_sheet_rows, cat_sheet_cols, 2);
              //   initialize_animation(&cat_animate3, cat_sheet_rows, cat_sheet_cols, 3);
              //   printf("got here");
              // }
          }
          break;
      }
    }

    // randomly change speed
    if (rand() % 70000000 == 0) {
      speed = rand() % 10 + 1;
      printf("Changing speed to %i\n", speed);
    }

    cycle++;
    if (cycle == SMOOTHNESS) {
      // only update random num if the sprite has pseudo-lerped to another spot
      direction = generate_random(0, 5, &prev);
      cycle = 0;
    }
    move_random_direction(direction, &cat_box, speed, &prev);
    SDL_RenderClear(init.renderer);
    SDL_RenderCopy(init.renderer, init.texture, NULL, NULL);

    switch (direction) {
    case 0:
      loop_Animation(&cat_animate3, init.renderer, &cat_box);
      break;
    case 1:
      loop_Animation(&cat_animate, init.renderer, &cat_box);
      break;
    case 2:
      loop_Animation(&cat_animate1, init.renderer, &cat_box);
      break;
    case 3:
      loop_Animation(&cat_animate2, init.renderer, &cat_box);
      break;
    default:
      loop_Animation(&cat_animate, init.renderer, &cat_box);
      break;
    }

    SDL_RenderPresent(init.renderer);

    // put this in a function
    Uint64 time_end = SDL_GetPerformanceCounter();
    // find elapse time
    float elapsed_time = (time_end - time_start) /
                         (float)SDL_GetPerformanceFrequency() * 1000.0F;

    // cap fps at 60
    SDL_Delay(floorf(16.666F - elapsed_time));
  }

  end_program(init.texture, cat_texture, init.renderer, init.window);
  return 0;
}
