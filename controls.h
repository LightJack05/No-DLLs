#ifndef CONTROLS_H
#define CONTROLS_H
#include <stdbool.h>

#include "SDL2/SDL.h"

extern bool Controls_WDown;
extern bool Controls_SDown;
extern bool Controls_ADown;
extern bool Controls_DDown;

void Controls_KeyDown(SDL_Keycode sym);
void Controls_KeyUp(SDL_Keycode sym);

#endif // CONTROLS_H