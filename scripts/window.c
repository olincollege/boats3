#include <stdio.h> /* printf and fprintf */
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

//sudo apt-get install libsdl2-dev
// use compiler flags -lSDL2 and -lSDL2_image
// gcc -o window scripts/window.c -lSDL2 -lSDL2_image
//sudo apt-get install libsdl2-image

/* Sets constants */
// replace the width and height with screen size
#define WIDTH 1920  // this is based on the background image size currently
#define HEIGHT 1080
#define DELAY 3000



void end_program(SDL_Texture *texture, SDL_Surface *image, SDL_Renderer *renderer, SDL_Window *window) {
  SDL_DestroyTexture(texture);
  printf("got here 4\n");
  SDL_FreeSurface(image);
  printf("got here 5\n");
  SDL_DestroyRenderer(renderer);
  printf("got here 6\n");
  SDL_DestroyWindow(window);
  printf("got here 7\n");
  SDL_Quit();
  printf("got here 8\n");
}




int main(int argc, char **argv) {
  /* Initialises data */
  SDL_Window *window = NULL;

  bool quit = false;
  SDL_Event event;

  /*
  * Initialises the SDL video subsystem (as well as the events subsystem).
  * Returns 0 on success or a negative error code on failure using SDL_GetError().
  */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
	  printf("Error SDL2_image Initialization\n");
    return 2;
  }

  // Creates a SDL window
  window = SDL_CreateWindow("SDL Example", /* Title of the SDL window */
                            SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
                            SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
                            WIDTH, /* Width of the window in pixels */
                            HEIGHT, /* Height of the window in pixels */
                            SDL_WINDOW_BORDERLESS ||
                            SDL_WINDOW_MAXIMIZED); /* Additional flag(s) */
  
  // Checks if window has been created; if not, exits program
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 3;
  }

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("renderer error\n");
    return 4;
  }

  if (SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT) != 0){
    printf("resolution setting error\n");
    printf("%s\n", SDL_GetError());
    return 5;
  }

  SDL_Surface * image = IMG_Load("background.png");
  if (image == NULL) {
	  printf("error loading image\n");
    return 6;
  }

  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL) {
    printf("error creating texture\n");
    return 7;
  }


  fprintf(stdout, "window initialized\n");
  while (!quit) {
    SDL_WaitEvent(&event);

    switch (event.type)
    {    
      // if you press a key
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
          printf("got here\n");
          quit = true;
          break;
        }

        //break out of larger SDL_KEYDOWN
        break;  
            
      case SDLK_ESCAPE:
        quit = true;
        break;

      case SDL_QUIT:
        quit = true;
        break;
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  end_program(texture, image, renderer, window);
  
  return 0;
}
