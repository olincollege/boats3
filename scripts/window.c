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

//this is a global

bool quit = false;


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


void Handle_Event(SDL_Event event){

    switch (event.type)
      {    
        //if you press a key
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){

              case SDLK_ESCAPE:
              quit = true;
              break;
            }
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

      case SDL_QUIT:
        quit = true;
        break;
    }
}

}

int main(int argc, char **argv) {
  /* Initialises data */
  SDL_Window *window = NULL;

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
  /*
  if (SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT) != 0){
    printf("resolution setting error\n");
    printf("%s\n", SDL_GetError());
    return 5;
  }//*/

  SDL_Surface * image = IMG_Load("assets/background.png");
  if (image == NULL) {
	  printf("error loading image\n");
    return 6;
  }

  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL) {
    printf("error creating texture\n");
    return 7;
  }

  SDL_Surface * boat_image = IMG_Load("assets/boat.png");
  if (image == NULL) {
	  printf("error loading image\n");
    return 6;
  }

  SDL_Texture * boat_texture = SDL_CreateTextureFromSurface(renderer, boat_image);
  if (texture == NULL) {
    printf("error creating texture\n");
    return 7;
  }

  SDL_Rect dstrect;
  dstrect.x = 20;
  dstrect.y = 20;
  dstrect.w = 350;
  dstrect.h = 350;

  SDL_Rect dstrect2;
  dstrect2.x = 500;
  dstrect2.y = 0;
  dstrect2.w = 550;
  dstrect2.h = 350;

  int cycle = 0;

  fprintf(stdout, "window initialized\n");
  while (!quit) {

    cycle++;
    cycle = cycle%2;

    if (SDL_PollEvent(&event)){
      Handle_Event(event);
    }


    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    printf("%i\n",cycle);
    if (cycle){
      SDL_RenderCopy(renderer, boat_texture, NULL, &dstrect);
    }
    else{
      SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
    }
    SDL_RenderPresent(renderer);
  }
  

  SDL_DestroyTexture(boat_texture);
  printf("got here 4\n");
  SDL_FreeSurface(boat_image);
  printf("got here 5\n");

  end_program(texture, image, renderer, window);

  
  
  return 0;
}
