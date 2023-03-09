/**
 * Random generated movement algorithm #1. rand() is used to generate a number
 * that corresponds to the direction that the sprite will move in.
*/
#pragma once

#include <stdio.h>
#include <time.h>

/**
 * Generates a random integer within the range [minimum, maximum) given two
 * integers representing a lower and upper bound (latter not inclusive).
 * 
 * Uses `rand()` * % (maximum-minimum) + minimum in order to limit the range 
 * of the values produced from `rand()`.
 * 
 * @param min   An integer representing the minimum value.
 * @param max   An integer representing the maximum value.
 * @return  An integer representing the random number generated within the given
 *  range.
*/
int generate_random(int min, int max);

/**
 * Moves the sprite up within the window.
 * 
 * @param sprite A pointer to a rectangle object representing the size and
 * position of the sprite within the window 
 * @param distance An int representing how many pixels the sprite should be
 * moved per function call
*/
void move_up(SDL_Rect *sprite, int distance);

/**
 * Moves the sprite down towards the bottom of a window.
 * 
 * @param sprite A pointer to a rectangle object representing the size and
 * position of the sprite within the window 
 * @param distance An int representing how many pixels the sprite should be
 * moved per function call
*/
void move_down(SDL_Rect *sprite, int distance);

/**
 * Moves the sprite left within a window.
 * 
 * @param sprite A pointer to a rectangle object representing the size and
 * position of the sprite within the window 
 * @param distance An int representing how many pixels the sprite should be
 * moved per function call
*/
void move_left(SDL_Rect *sprite, int distance);

/**
 * Moves the sprite right within a window.
 * 
 * @param sprite A pointer to a rectangle object representing the size and
 * position of the sprite within the window 
 * @param distance An int representing how many pixels the sprite should be
 * moved per function call
*/
void move_right(SDL_Rect *sprite, int distance);

/**
 * Runs end of program cleanup
 * 
 * @param texture A pointer to a texture representing the background image
 * @param boat_texture A pointer to a texture representing the boat sprite
 * @param renderer The window's renderer object
 * @param window The window object
*/
void end_program(SDL_Texture *texture, SDL_Surface *image,
                 SDL_Renderer *renderer, SDL_Window *window);
