/*
The controller, responsible for handling inputs from the user.
*/

#pragma once

#include <SDL2/SDL_image.h>

/**
 * Handle an event
 *
 * Given an SDL event queue, identify what event is occurring
 * (generally, what key is being pressed) and return a number
 * corresponding to a behavior in the main game loop.
 *
 * @param event An SDL event queue to manage
 *
 * @return An integer corresponding to the behavior that should occur in the
 *loop 0 = Quit, 1 = Change speed, 2 = Change color.
 **/
int handle_event(SDL_Event event);
