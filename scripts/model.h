/**
 *  A simple model for our desktop pet
 */

#pragma once

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 1920 // this is based on the background image size currently
#define HEIGHT 1080
#define DELAY 3000

// Decide whether or not to quit

typedef struct sprite {
  SDL_Texture *texture;
  SDL_Rect *rect;
  const char *path;
} sprite;

typedef struct animation {
  SDL_Texture *texture;
  int width;
  int height;
  int ypos;
  int num_frames;
  int frames_loop[30];
  int frame_index;
  int super_animation_index;
} animation;

typedef struct initialized_state {
  SDL_Window *window;
  SDL_Texture *texture;
  SDL_Renderer *renderer;
  SDL_Surface *background;
} state;

extern state init;

state setup_state(state init);

/**
 * Runs the cleanup commands when exiting the program.
 *
 * @param texture An SDL_Texture created from the SDL_Surface object
 * @param image An SDL_Surface representing the image object
 * @param renderer A renderer object
 * @param window An SDL_Window representing the popup window.
 */
void end_program(SDL_Texture *texture, SDL_Surface *image,
                 SDL_Renderer *renderer, SDL_Window *window);

void loop_Animation(animation *loop, SDL_Renderer *renderer, SDL_Rect *box_ptr);

int find_sprite_grid(SDL_Texture *texture, int*row_height,int*column_width,int num_rows, int num_columns);
int initialize_animation(animation* loop,
                          int num_rows,int num_col,int row_number);
                          
SDL_Texture * initialize_texture(const char* filepath, SDL_Renderer * renderer);
int make_animation_box(SDL_Rect * box,animation *loop,int xpos, int ypos,float scale);
void animate_sequential(SDL_Renderer * renderer,animation * animations[10],SDL_Rect *box,int num_animations);
