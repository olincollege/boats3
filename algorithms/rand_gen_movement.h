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
 * Documentification
*/
void move_up(void);

/**
 * Documentification
*/
void move_down(void);

/**
 * Documentification
*/
void move_left(void);

/**
 * Documentification
*/
void move_right(void);
