/**
 *  A simple model for a desktop pet
 */

#pragma once

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

// Defines the resolution of the screen.
#define WIDTH 1920
#define HEIGHT 1080

// Define starting position and size of sprite.
#define SPRITE_X 50
#define SPRITE_Y 50
#define SPRITE_WIDTH 550
#define SPRITE_HEIGHT 350

// Defines smoothness of sprite movement.
// Int from 0-10; a higher number = smoother .
#define SMOOTHNESS 10

// TO DO: refactor main.c and model.c code to rely on these global constants
// instead of passing lots of parameters #define WALK_GRAY =
// {0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1}; #define WALK_WHITE =
// {3,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,5,4,4,4,4,4,4}; #define WALK_BLACK =
// {6,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,8,7,7,7,7,7,7}; #define WALK_ORANGE =
// {9,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,11,10,10,10,10,10,10};

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
 * Determines a frame rectangle's dimensions.
 *
 * Sets the given pointers to row height and column width of the frames to the
 * height of the texture divided by the number of rows and the width of the
 * texture divided of the number of columns, respectively.
 *
 * @param texture The given SDL_Texture corresponding with the rectangle.
 * @param row_height  An integer pointer representing the height of a row on the
 *  sprite sheet, in pixels.
 * @param column_width  An integer pointer representing the width of a row on
 *  the sprite sheet, in pixels.
 * @param num_rows  An integer representing the number of rows in the sprite
 *  sheet.
 * @param num_columns An integer representing the number of columns in the
 * sprite sheet.
 * @return 1 if SDL_QueryTexture returns an error; otherwise, 0.
 */
int find_sprite_grid(SDL_Texture *texture, int *row_height, int *column_width,
                     int num_rows, int num_columns);

/**
 * Initializes an animation.
 *
 * Individually sets the number of rows, columns, frames, and frame loop content
 * for each animation. Assumes that the texture, number of frames, and frame
 * loop parameters of the given animation have already been set.
 *
 * @param loop  A pointer to the given animation struct.
 * @param num_rows  The number of rows in the sprite sheet corresponding with
 *  the animation.
 * @param num_col The number of columns in the sprite sheet corresponding with
 *  the animation.
 * @param row_number  []
 */
int initialize_animation(animation *loop, int num_rows, int num_col,
                         int row_number);

/**
 * Initializes and SDL Texture from an image given a file path.
 *
 * Creates a surface with the given file path which a texture is then generated
 * from. The surface used to make the texture is then freed.
 *
 * @param filepath  A string representing the image of the sprite's location.
 * @param renderer  An SDL_Renderer representing the current window to display
 *  images on.
 */
SDL_Texture *initialize_texture(const char *filepath, SDL_Renderer *renderer);

/**
 * Generates a random number within the range [min, max).
 *
 * The random generation involves custom probabilities to simulate a more
 * realistic movement pattern; if a given number was chosen the last time this
 * function was called, it has a 40% chance to get picked again, as opposed to
 * everything else at 20%.
 *
 * @param min An integer representing the lower (inclusive) bound of the range
 *  to generate from.
 * @param max An integer representing the lower (exclusive) bound of the range
 *  to generate from.
 * @param prev An integer pointer representing the previously-chosen number.
 *
 * @return An integer representing the random number generated.
 */
int generate_random(int min, int max, int *prev);

/**
 * Moves the sprite towards the bottom of the screen.
 *
 * Updates the sprite's rectangular coordinates to move it down within the
 * window. If the sprite is at the lower bound of the window, it instead
 * moves the sprite up.
 *
 * @param sprite An SDL_Rect pointer representing the position and size of the
 * sprite image.
 * @param distance An int representing the number of pixels to travel.
 */
int move_down(SDL_Rect *sprite, int distance);

/**
 * Moves the sprite towards the top of the screen.
 *
 * Updates the sprite's rectangular coordinates to move it up within the
 * window. If the sprite is at the upper bound of the window, it instead
 * moves the sprite down.
 *
 * @param sprite An SDL_Rect pointer representing the position and size of the
 * sprite image.
 * @param distance An integer representing the number of pixels to travel.
 */
int move_up(SDL_Rect *sprite, int distance);

/**
 * Moves the sprite towards the left of the screen.
 *
 * Updates the sprite's rectangular coordinates to move it left within the
 * window. If the sprite is at the left bound of the window, it instead
 * moves the sprite right.
 *
 * @param sprite An SDL_Rect pointer representing the position and size of the
 * sprite image.
 * @param distance An int representing the number of pixels to travel.
 */
int move_left(SDL_Rect *sprite, int distance);

/**
 * Moves the sprite towards the right of the screen.
 *
 * Updates the sprite's rectangular coordinates to move it right within the
 * window. If the sprite is at the right bound of the window, it instead
 * moves the sprite left.
 *
 * @param sprite An SDL_Rect pointer representing the position and size of the
 * sprite image.
 * @param distance An int representing the number of pixels to travel.
 */
int move_right(SDL_Rect *sprite, int distance);

/**
 * Based on an integer value (1-5), calls the corresponding sprite movement
 * function.
 *
 * Numbers 0, 1, 2, 3 represent moving up, down, left, and right. Number 4
 * represents staying in place, or idling. The default is to idle.
 *
 * @param num An integer representing a randomly-generated number corresponding
 *  to a directional movement (or lack thereof).
 * @param sprite_pos An SDL_Rect pointer representing the pixel position and
 * size of the sprite within the window.
 * @param distance An integer representing the number of pixels to travel.
 * @param prev An integer pointer representing the previously-chosen number.
 */
void move_random_direction(int num, SDL_Rect *sprite_pos, int distance,
                           int *prev);

/**
 * Runs the cleanup commands when exiting the program.
 *
 * @param bg_texture An SDL_Texture pointer representing the background image.
 * @param sprite_texture An SDL_Texture pointer representing the sprite image.
 * @param renderer A renderer object, used to render the images into the window.
 * @param window An SDL_Window representing the window that pops up.
 */
void end_program(SDL_Texture *bg_texture, SDL_Texture *sprite_texture,
                 SDL_Renderer *renderer, SDL_Window *window);

/**
 * Loops through the frames of an animation from a sprite sheet.
 *
 * Crops a frame from a sprite sheet and then cycles through other available
 * frames that are present in the given animation.
 *
 * @param loop  A pointer to an animation struct that holds the frame
 *  information.
 * @param renderer  An SDL_Renderer representing the current window to display
 *  images on.
 */
void loop_Animation(animation *loop, SDL_Renderer *renderer, SDL_Rect *box_ptr);

/**
 * Creates a rectangle in which the animation loop will be run onto.
 *
 * Scales the animation to the size of the rectangle.
 *
 * @param box   A pointer to an SDL_Rect that the animation will be run on.
 * @param loop  A pointer to the animation struct containing the information for
 *  the sprite loop.
 * @param xpos  An integer representing the x position of the rectangle.
 * @param ypos  An integer representing the y position of the rectangle.
 * @param scale An integer representing how much to scale the image by to match
 *  the rectangle.
 */
int make_animation_box(SDL_Rect *box, animation *loop, int xpos, int ypos,
                       float scale);

void change_cat_color(animation *cat0, animation *cat1, animation *cat2,
                      animation *cat3, int *new_frame_loop);
