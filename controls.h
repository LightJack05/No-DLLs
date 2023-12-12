#ifndef CONTROLS_H
#define CONTROLS_H
#include <stdbool.h>

#include "SDL2/SDL.h"

extern bool Controls_W;
extern bool Controls_S;
extern bool Controls_A;
extern bool Controls_D;

extern bool Controls_WUp;
extern bool Controls_SUp;
extern bool Controls_AUp;
extern bool Controls_DUp;

extern bool Controls_WDown;
extern bool Controls_SDown;
extern bool Controls_ADown;
extern bool Controls_DDown;

void Controls_KeyDown(SDL_Keycode sym);
void Controls_KeyUp(SDL_Keycode sym);
void ResetKeyUpDown();

#endif // CONTROLS_H