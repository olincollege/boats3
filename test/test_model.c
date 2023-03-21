#include <SDL2/SDL_image.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../scripts/model.h"

// NOLINTBEGIN(*-magic-numbers)

/* Check that calling move_down returns the number corresponding with the "down"
 * direction (0) when the given rectangle does not have the boundary directly
 * below it.*/
Test(test_model, down_default) {
  SDL_Rect test_rect = {0, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_down(&test_rect, 10);
  cr_assert(eq(int, 0, dir));
}

/* Check that calling move_down returns the number corresponding with the "up"
 * direction (1) when the given rectangle has the boundary directly below it. */
Test(test_model, down_boundary) {
  SDL_Rect test_rect = {0, HEIGHT - SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
  int dir = move_down(&test_rect, 10);
  cr_assert(eq(int, 1, dir));
}

/* Check that calling move_random_direction with the down input when not at
 * the boundary updates prev to the number corresponding with the "down"
 * direction (0). */
// NOLINTEND(*-magic-numbers)
