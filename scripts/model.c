/*
Contains the model of our system including the location of sprite, status of
sprite (what image it is), the intended direction of movement of the sprite,
etc.
*/

#include "model.h"

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int find_sprite_grid(SDL_Texture *texture, int *row_height, int *column_width,
                     int num_rows, int num_columns) {
  // function for automatically finding frame rectangles dimensions
  //  CMAKE WARNING: wants height and width to be initialize
  int height_texture = 0;
  int width_texture = 0;
  if (0 !=
      SDL_QueryTexture(texture, NULL, NULL, &width_texture, &height_texture)) {
    (void)fprintf(stderr, "QueryTexture Error in find_sprite_grid.\n");
    return 1;
  }

  *row_height = height_texture / num_rows;
  *column_width = width_texture / num_columns;

  return 0;
}

int initialize_animation(animation *loop, int num_rows, int num_col,
                         int row_number) {
  // bounds check the initialization
  if (row_number > num_rows) {
    (void)fprintf(stderr, "row number too large for texture.");
    return 1;
  }
  int row_height = 0;
  int column_width = 0;
  if (find_sprite_grid(loop->texture, &row_height, &column_width, num_rows,
                       num_col)) {
    (void)fprintf(stderr, "Error Initializing animation.");
    return 1;
  }

  // initialize to frame 0 in loop
  loop->width = column_width;
  loop->height = row_height;
  loop->ypos = row_height * row_number;

  // initialize to first frame
  loop->frame_index = 0;

  return 0;
}

SDL_Texture *initialize_texture(const char *filepath, SDL_Renderer *renderer) {
  SDL_Surface *image = IMG_Load(filepath);
  if (image == NULL) {
    (void)fprintf(stderr, "Surface creation error.");
    return NULL;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL) {
    (void)fprintf(stderr, "Texture creation error.");
    return NULL;
  }

  SDL_FreeSurface(image);
  return texture;
}

int generate_random(int min, int max, int prev) {
  int random_val = prev;
  const int probability_baseline = 10;
  int probability =
      rand() % probability_baseline; // NOLINT(cert-msc30-c, cert-msc50-cpp)
  if (probability > 4) {
    random_val =
        rand() % (max - min) + min; // NOLINT(cert-msc30-c, cert-msc50-cpp)
  }
  return random_val;
}

int move_up(SDL_Rect *sprite, int distance) {
  if (sprite->y > 0) {
    sprite->y -= distance;
    return 0;
  }
  sprite->y += distance;
  return 1;
}

int move_down(SDL_Rect *sprite, int distance) {
  if (sprite->y < HEIGHT - SPRITE_HEIGHT) {
    sprite->y += distance;
    return 1;
  }
  sprite->y -= distance;
  return 0;
}

int move_left(SDL_Rect *sprite, int distance) {
  if (sprite->x > 0) {
    sprite->x -= distance;
    return 2;
  }
  sprite->x += distance;
  return 3;
}

int move_right(SDL_Rect *sprite, int distance) {
  if (sprite->x < WIDTH - SPRITE_WIDTH) {
    sprite->x += distance;
    return 3;
  }
  sprite->x -= distance;
  return 2;
}

void move_random_direction(int num, SDL_Rect *sprite_pos, int distance,
                           int *prev) {
  switch (num) {
  case 0:
    *prev = move_up(sprite_pos, distance);
    break;
  case 1:
    *prev = move_down(sprite_pos, distance);
    break;
  case 2:
    *prev = move_left(sprite_pos, distance);
    break;
  case 3:
    *prev = move_right(sprite_pos, distance);
    break;
  case 4:
    // do nothing/idle (walks in place)
    *prev = 4;
    break;
  default:
    *prev = move_up(sprite_pos, distance);
    printf("Default case reached.\n");
    break;
  }
}

void end_program(SDL_Texture *bg_texture, SDL_Texture *sprite_texture,
                 SDL_Renderer *renderer, SDL_Window *window) {
  SDL_DestroyTexture(bg_texture);
  SDL_DestroyTexture(sprite_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  printf("Successfully exited program.\n");
}

void loop_animation(animation *loop, SDL_Renderer *renderer,
                    SDL_Rect *box_ptr) {
  int xpos = 0;

  xpos = loop->frames_loop[loop->frame_index] * loop->width;

  SDL_Rect crop_sprite = {
      .x = xpos, .y = loop->ypos, .w = loop->width, .h = loop->height};

  if (0 != SDL_RenderCopy(renderer, loop->texture, &crop_sprite, box_ptr)) {
    (void)fprintf(stderr, "Error animating.");
  }
  //  update the position in the loop
  loop->frame_index = loop->frame_index + 1;
  loop->frame_index = loop->frame_index % loop->num_frames;
}

int make_animation_box(SDL_Rect *box, animation *loop, int xpos, int ypos,
                       float scale) {
  box->x = xpos;
  box->y = ypos;
  box->w = floor(loop->width * scale);
  box->h = floor(loop->height * scale);

  return 0;
}

void change_cat_color(animation *cat0, animation *cat1, animation *cat2,
                      animation *cat3, int new_frame_loop[MAX_ANIMATION_LEN]) {
  cat0->frames_loop = new_frame_loop;
  cat1->frames_loop = new_frame_loop;
  cat2->frames_loop = new_frame_loop;
  cat3->frames_loop = new_frame_loop;
}

void change_random_cat_color(animation *cat0, animation *cat1, animation *cat2,
                             animation *cat3, int orange[MAX_ANIMATION_LEN],
                             int black[MAX_ANIMATION_LEN],
                             int white[MAX_ANIMATION_LEN],
                             int gray[MAX_ANIMATION_LEN]) {
  int current_frame_loop = cat0->frame_index;

  int case_no =
      rand() % 3; // NOLINT(cert-msc30-c, cert-msc50-cpp concurrency-mt-unsafe)
  // default case
  switch (case_no) {
  case 0:
    if (current_frame_loop != black) {
      change_cat_color(cat0, cat1, cat2, cat3, black);
    }
    break;
  case 1:
    if (current_frame_loop != white) {
      change_cat_color(cat0, cat1, cat2, cat3, white);
    }
    break;
  case 2:
    if (current_frame_loop != gray) {
      change_cat_color(cat0, cat1, cat2, cat3, gray);
    }
    break;
  default:
    change_cat_color(cat0, cat1, cat2, cat3, orange);
    break;
  }
}
