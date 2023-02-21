#include <stdio.h> /* printf and fprintf */
#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL_image.h>

//sudo apt-get install libsdl2-dev
// use compiler flags -lSDL2 and -lSDL2_image 
//sudo apt-get install libsdl2-image

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

int main (int argc, char **argv)
{
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
	  printf("Error SDL2_image Initialization");
	return 2;
}

  /* Creates a SDL window */
  window = SDL_CreateWindow("SDL Example", /* Title of the SDL window */
			    SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
			    SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
			    WIDTH, /* Width of the window in pixels */
			    HEIGHT, /* Height of the window in pixels */
			    SDL_WINDOW_BORDERLESS ||
          SDL_WINDOW_MAXIMIZED); /* Additional flag(s) */
  
  /* Checks if window has been created; if not, exits program */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
	    printf("renderer error");
	return 4;
}
  SDL_Surface * image = IMG_Load("boat.png");
  if (image == NULL) {
	  printf("error loading image");
	return 5;
}


  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

  if (texture == NULL) {
	  printf("error creating texture");
	return 6;
}



  //dont remember why we need this but apparently it prevents memory leaks
  SDL_FreeSurface(image);
  /* Pauses all SDL subsystems for a variable amount of milliseconds */
  while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDLK_ESCAPE:
            quit = true;
            break;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        //printf("got here");
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  
  return 0;
}
