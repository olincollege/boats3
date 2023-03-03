#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h> /* printf and fprintf */
#include <stdlib.h>

// sudo apt-get install libsdl2-dev
//  use compiler flags -lSDL2 and -lSDL2_image
//  gcc -o window scripts/window.c -lSDL2 -lSDL2_image
// sudo apt-get install libsdl2-image

/* Sets constants */
// replace the width and height with screen size
#define WIDTH 1920 // this is based on the background image size currently
#define HEIGHT 1080
#define DELAY 3000

// this is a global

bool quit = false;

typedef struct sprite {
  SDL_Texture *texture;
  SDL_Rect *rect;
  const char *path;
} sprite;

typedef struct Animation {
  SDL_Texture *texture;
  int width;
  int height;
  int ypos;
  int num_frames;
  int frames_loop[30];
  int frame_index;
} Animation;

// Animation kittykat = {

void loop_Animation(Animation *loop, SDL_Renderer *renderer,
                    SDL_Rect *box_ptr) {

  int xpos;

  xpos = loop->frames_loop[loop->frame_index] * loop->width;
  // printf("%d\n", xpos);

  SDL_Rect crop_sprite = {
      .x = xpos, .y = loop->ypos, .w = loop->width, .h = loop->height};

  if (0 != SDL_RenderCopy(renderer, loop->texture, &crop_sprite, box_ptr)) {
    printf("error animating");
  }
  // update the position in the loop
  loop->frame_index = loop->frame_index + 1;
  loop->frame_index = loop->frame_index % loop->num_frames;
}

void end_program(SDL_Texture *texture, SDL_Surface *image,
                 SDL_Renderer *renderer, SDL_Window *window) {
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

int main(int argc, char **argv) {
  /* Initialises data */
  SDL_Window *window = NULL;

  SDL_Event event;

  /*
   * Initialises the SDL video subsystem (as well as the events subsystem).
   * Returns 0 on success or a negative error code on failure using
   * SDL_GetError().
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
  window = SDL_CreateWindow(
      "SDL Example",           /* Title of the SDL window */
      SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
      SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
      WIDTH,                   /* Width of the window in pixels */
      HEIGHT,                  /* Height of the window in pixels */
      SDL_WINDOW_BORDERLESS || SDL_WINDOW_MAXIMIZED); /* Additional flag(s) */

  // Checks if window has been created; if not, exits program
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 3;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

  SDL_Surface *image = IMG_Load("assets/background.png");
  if (image == NULL) {
    printf("error loading image\n");
    return 6;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL) {
    printf("error creating texture\n");
    return 7;
  }

  SDL_Surface *boat_image = IMG_Load("assets/boat.png");
  if (image == NULL) {
    printf("error loading image\n");
    return 6;
  }

  SDL_Texture *boat_texture =
      SDL_CreateTextureFromSurface(renderer, boat_image);
  if (texture == NULL) {
    printf("error creating texture\n");
    return 7;
  }

  SDL_Surface *cat_image = IMG_Load("assets/Catsprites.png");
  if (image == NULL) {
    printf("error loading image\n");
    return 6;
  }

  SDL_Texture *cat_texture = SDL_CreateTextureFromSurface(renderer, cat_image);
  if (texture == NULL) {
    printf("error creating texture\n");
    return 7;
  }

  /*const char *hpath = "assets/boat.png";
  SDL_Surface *husky_image = IMG_Load(hpath);
  SDL_Texture *husky_texture =
      SDL_CreateTextureFromSurface(renderer, husky_image);
  SDL_Rect husky_rect = {500, 0, 350, 350};*/

  // sprite husky = {husky_texture, &husky_rect, hpath};
  SDL_Rect husky_rect = {0, 500, 350, 350};
  sprite husky = {
      SDL_CreateTextureFromSurface(renderer, IMG_Load("assets/boat.png")),
      &husky_rect, "assets/boat.png"};

  // sprite husky = {husky_texture, &(sprite){500, 0, 350, 350}, hpath};

  SDL_Rect dstrect = {500,0,350,350};

  SDL_Rect dstrect2 = {500,500,550,350};

  SDL_Rect dstrect3 = {0,0,200,200};

  SDL_Rect srcrect2 = {0,0,100,100};

  // kittykat spritesheet
  /*
    typedef struct Animation{
    SDL_Texture * texture;
    int width;
    int height;
    int ypos;
    int num_frames;
    int frames_loop[30];
    int frame_index;
  }Animation;//*/

  Animation kittykat_walk = {.texture = boat_texture,
                             .width = 200,
                             .height = 200,
                             .ypos = 200,
                             .num_frames = 7,
                             .frames_loop = {0, 1, 2, 2, 2, 2, 1},
                             .frame_index = 0};

  int cycle = 0;

  fprintf(stdout, "window initialized\n");
  while (!quit) {
    cycle++;
    cycle = cycle % 2;

    if (SDL_PollEvent(&event)) {
      Handle_Event(event);
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderCopy(renderer, husky.texture, NULL, husky.rect);

    // printf("%i\n",cycle);
    if (cycle) {
      SDL_RenderCopy(renderer, boat_texture, NULL, &dstrect);

    } else {
      // test of the crop image feature
      SDL_RenderCopy(renderer, texture, &srcrect2, &dstrect2);
    }
    loop_Animation(&kittykat_walk, renderer, &dstrect3);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(boat_texture);
  printf("got here 4\n");
  SDL_FreeSurface(boat_image);
  printf("got here 5\n");
  // SDL_DestroyTexture(husky.texture);

  end_program(texture, image, renderer, window);

  return 0;
}
