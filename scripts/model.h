/**
 *  A simple model for our desktop pet
 */

#pragma once

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 1920
#define HEIGHT 1080
// Define starting position and size of sprite
#define SPRITE_X 50
#define SPRITE_Y 50
#define SPRITE_WIDTH 550
#define SPRITE_HEIGHT 350

// defines smoothness of sprite movement. Int from 0-10. Higher number = smoother movement
#define SMOOTHNESS 10

// #define DELAY 3000

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
  int *frames_loop;
  // int frames_loop[30];
  int frame_index;
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
 * to do: write docs
 *
 * @param loop _______________
 */
int initialize_animation(animation* loop, int num_rows, int num_col,
                         int row_number);

/**
 * Generates a random number within the range [min, max).
 * 
 * The random generation involves custom probabilities to simulate a more
 * realistic movement pattern. Also updates the value of `prev` to the newly
 * generated number.
 *
 * @param min An int representing the lower (inclusive) bound of the range to
 * generate from
 * @param max An int representing the lower (exclusive) bound of the range to
 * generate from
 * @param prev An int pointer representing the previously-chosen number
 *
 * @return An int representing the random number generated
 */
int generate_random(int min, int max, int *prev);

/**
 * Moves the sprite towards the top of the screen.
 * 
 * Updates the sprite's rectangular coordinates to move it up within the
 * window. If the sprite is at the upper bound of the window, it instead
 * moves the sprite down and changes the value of `prev` to reflect this.
 *
 * @param sprite An SDL_Rect pointer representing the position and size of the
 * sprite image
 * @param distance An int representing the number of pixels to travel
 * @param prev An int pointer representing the previously-chosen number
 */
void move_up(SDL_Rect *sprite, int distance, int *prev);

/**
 * Moves the sprite towards the bottom of the screen.
 * 
 * Updates the sprite's rectangular coordinates to move it down within the
 * window. If the sprite is at the lower bound of the window, it instead
 * moves the sprite up and changes the value of `prev` to reflect this.
 *
 * @param sprite An SDL_Rect pointer representing the position and size of the
 * sprite image
 * @param distance An int representing the number of pixels to travel
 * @param prev An int pointer representing the previously-chosen number
 */
void move_down(SDL_Rect *sprite, int distance, int *prev);

/**
 * Moves the sprite towards the left of the screen.
 * 
 * Updates the sprite's rectangular coordinates to move it left within the
 * window. If the sprite is at the left bound of the window, it instead
 * moves the sprite right and changes the value of `prev` to reflect this.
 *
 * @param sprite An SDL_Rect pointer representing the position and size of the
 * sprite image
 * @param distance An int representing the number of pixels to travel
 * @param prev An int pointer representing the previously-chosen number
 */
void move_left(SDL_Rect *sprite, int distance, int *prev);

/**
 * Moves the sprite towards the right of the screen.
 * 
 * Updates the sprite's rectangular coordinates to move it right within the
 * window. If the sprite is at the right bound of the window, it instead
 * moves the sprite left and changes the value of `prev` to reflect this.
 *
 * @param sprite An SDL_Rect pointer representing the position and size of the
 * sprite image
 * @param distance An int representing the number of pixels to travel
 * @param prev An int pointer representing the previously-chosen number
 */
void move_right(SDL_Rect *sprite, int distance, int *prev);

/**
 * Based on an integer value (1-5), calls the corresponding sprite movement
 * function.
 * 
 * Numbers 0, 1, 2, 3 represent moving up, down, left, and right. Number 5
 * represents staying in place, or idling. The default is to idle.
 *
 * @param num An int representing a randomly-generated number corresponding to
 * a directional movement (or lack thereof)
 * @param sprite_pos An SDL_Rect pointer representing the pixel position and
 * size of the sprite within the window
 * @param distance An int representing the number of pixels to travel
 * @param prev An int pointer representing the previously-chosen number
 */
void move_random_direction(int num, SDL_Rect *sprite_pos, int distance, int *prev);

/**
 * Runs the cleanup commands when exiting the program.
 *
 * @param bg_texture An SDL_Texture pointer representing the background image
 * @param sprite_texture An SDL_Texture pointer representing the sprite image
 * @param renderer A renderer object, used to render the images into the window
 * @param window An SDL_Window representing the popup window
 */
void end_program(SDL_Texture *bg_texture, SDL_Texture *sprite_texture,
                 SDL_Renderer *renderer, SDL_Window *window);

void loop_Animation(animation *loop, SDL_Renderer *renderer, SDL_Rect *box_ptr);

int find_sprite_grid(SDL_Texture *texture, int *row_height, int *column_width, int num_rows, int num_columns);

SDL_Texture* initialize_texture(const char* filepath, SDL_Renderer *renderer);

int make_animation_box(SDL_Rect *box, animation *loop, int xpos, int ypos, float scale);
