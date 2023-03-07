/*
The controller, responsible for handling inputs from the user.
*/

#pragma once

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>

extern bool quit = false;
/**
Handle an event

Given an SDL event queue, identify what event is occuring
(generally, what key is being pressed) and produce
the correct corresponding behavior

* @param event An SDL event queue to manage
**/
void Handle_Event(SDL_Event event);
