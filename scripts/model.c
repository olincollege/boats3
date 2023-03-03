/*
Contains the model of our system including the location of sprite, status of
sprite (what image it is), the intended direction of movement of the sprite,
etc.
*/

#include "model.h"

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h> /* printf and fprintf */
#include <stdlib.h>

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
} animation;

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

void loop_animation(animation *loop, SDL_Renderer *renderer,
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

sprite *initialize_sprite(SDL_Renderer *renderer, const char *sprite_path,
                          int x_i, int y_i, int width, int height) {
  SDL_Surface *sprite_surface = IMG_Load(sprite_path);
  if (sprite_surface == NULL) {
    fprintf(stderr, "Error loading image.\n");
    return 6;
  }

  SDL_Texture *sprite_texture =
      SDL_CreateTextureFromSurface(renderer, sprite_texture);
  if (sprite_texture == NULL) {
    fprintf(stderr, "Error creating texture.\n");
    return 7;
  }

  SDL_Rect sprite_rect = {x_i, y_i, width, height};

  sprite spr = {sprite_texture, &sprite_rect, sprite_path};

  SDL_FreeSurface(sprite_surface);

  return &spr;
}
