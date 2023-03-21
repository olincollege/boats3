#include <SDL2/SDL_image.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../scripts/model.h"

// NOLINTBEGIN(*-magic-numbers)

/* Check that calling move_up returns the number corresponding with the "down"
 * direction (0) when the given rectangle does not have the boundary directly
 * below it.*/
Test(test_model, up_default) {
  SDL_Rect test_rect = {0, HEIGHT - SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_up(&test_rect, 1);
  cr_assert(eq(int, 0, dir));
}

/* Check that calling move_up returns the number corresponding with the "up"
 * direction (1) when the given rectangle has the boundary directly below it. */
Test(test_model, up_boundary) {
  SDL_Rect test_rect = {0, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_up(&test_rect, 1);
  cr_assert(eq(int, 1, dir));
}

/* Check that calling move_down returns the number corresponding with the "down"
 * direction (1) when the given rectangle does not have the boundary directly
 * below it.*/
Test(test_model, down_default) {
  SDL_Rect test_rect = {0, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_down(&test_rect, 1);
  cr_assert(eq(int, 1, dir));
}

/* Check that calling move_down returns the number corresponding with the "up"
 * direction (0) when the given rectangle has the boundary directly below it. */
Test(test_model, down_boundary) {
  SDL_Rect test_rect = {0, HEIGHT - SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_down(&test_rect, 1);
  cr_assert(eq(int, 0, dir));
}

/* Check that calling move_left returns the number corresponding with the "down"
 * direction (0) when the given rectangle does not have the boundary directly
 * below it.*/
Test(test_model, left_default) {
  SDL_Rect test_rect = {WIDTH - SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_left(&test_rect, 1);
  cr_assert(eq(int, 2, dir));
}

/* Check that calling move_left returns the number corresponding with the "left"
 * direction (3) when the given rectangle has the boundary directly below it. */
Test(test_model, left_boundary) {
  SDL_Rect test_rect = {0, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_left(&test_rect, 1);
  cr_assert(eq(int, 3, dir));
}

/* Check that calling move_right returns the number corresponding with the
 * "right" direction (3) when the given rectangle does not have the boundary
 * directly below it.*/
Test(test_model, right_default) {
  SDL_Rect test_rect = {0, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_right(&test_rect, 1);
  cr_assert(eq(int, 3, dir));
}

/* Check that calling move_right returns the number corresponding with the
 * "right" direction (2) when the given rectangle has the boundary directly
 * below it. */
Test(test_model, right_boundary) {
  SDL_Rect test_rect = {WIDTH - SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_right(&test_rect, 1);
  cr_assert(eq(int, 2, dir));
}

/* Check that calling generate_random creates a number that is within the
 * expected range. Runs multiple times to ensure a higher probability that the
 * function is only generating numbers within the expected range.*/
Test(test_model, random_number_range) {
  int prev = 0;
  for (int i = 0; i < 100; i++) {
    int rand = generate_random(0, 5, &prev);
    prev = rand;
    cr_assert(all(rand >= 0 && rand < 5));
  }
}

/* Check that calling move_random_direction updates the previous move to match
 * the direction that the rectangle is moved to. */
Test(test_model, move_random_direction) {
  // Starting location chosen so that the boundary cases are not triggered.
  SDL_Rect test_rect = {10, 10, SPRITE_WIDTH, SPRITE_HEIGHT};
  int prev = 0;

  // Storing movement up.
  move_random_direction(0, &test_rect, 1, &prev);
  cr_assert(eq(int, 0, prev));

  // Storing movement down.
  move_random_direction(1, &test_rect, 1, &prev);
  cr_assert(eq(int, 1, prev));

  // Storing movement left.
  move_random_direction(2, &test_rect, 1, &prev);

  cr_assert(eq(int, 2, prev));

  // Storing movement right.
  move_random_direction(3, &test_rect, 1, &prev);
  cr_assert(eq(int, 3, prev));

  // Storing idle.
  move_random_direction(4, &test_rect, 1, &prev);
  cr_assert(eq(int, 4, prev));
}

// NOLINTEND(*-magic-numbers)
