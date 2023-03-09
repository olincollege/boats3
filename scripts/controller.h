/*
The controller, responsible for handling inputs from the user.
*/

#pragma once

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

/**
Handle an event

Given an SDL event queue, identify what event is occurring
(generally, what key is being pressed) and produce
the correct corresponding behavior

* @param quit A pointer to a bool representing whether the animation loop
* should continue running
* @param event An SDL event queue to manage
**/
void Handle_Event(bool *quit, SDL_Event event);
