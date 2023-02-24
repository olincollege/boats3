// show the sprite in the window
// change position


#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
// sudo apt-get install libsdl2-dev
// use compiler flag -lSDL2 to link to SDL2

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

int main (int argc, char **argv)
{
  // open a window
  /* Initialises data */
  SDL_Window *window = NULL;
  
  /*
  * Initialises the SDL video subsystem (as well as the events subsystem).
  * Returns 0 on success or a negative error code on failure using SDL_GetError().
  */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
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

  // Uncomment if using a mac
  SDL_PumpEvents();

  /* Pauses all SDL subsystems for a variable amount of milliseconds */
  SDL_Delay(DELAY);

  /* Frees memory */
  SDL_DestroyWindow(window);
  
  /* Shuts down all SDL subsystems */
  SDL_Quit(); 
  
  return 0;
}

int generate_random(int max, int min){
  // not inclusive min/max
  int random = rand() % (max - min) + min;
}

void move_up(void){

}

void move_down(void){

}

void move_left(void){

}

void move_right(void){

}

void move_random_direction(){
  int direction = generate_random(0, 4);

  switch(direction){
    case 0:
      move_up();
    case 1:
      move_down();
    case 2:
      move_left();
    case 3:
      move_right();
  }
}
