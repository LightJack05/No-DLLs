#ifndef CONTROLS_H
#define CONTROLS_H
#include <stdbool.h>

#include "SDL2/SDL.h"

#define ExternKeyMapping(Key)       \
    extern bool Controls_##Key;     \
    extern bool Controls_##Key##Up; \
    extern bool Controls_##Key##Down;

#define KeyMapping(Key)      \
    bool Controls_##Key;     \
    bool Controls_##Key##Up; \
    bool Controls_##Key##Down;

#define KeyMappingSwitchCaseDown(Key, SDLKeyCode) \
    case SDLKeyCode:                              \
        Controls_##Key = true;                    \
        Controls_##Key##Down = true;              \
        Controls_##Key##Up = false;               \
        break;

#define KeyMappingSwitchCaseUp(Key, SDLKeyCode) \
    case SDLKeyCode:                            \
        Controls_##Key = false;                 \
        Controls_##Key##Down = false;           \
        Controls_##Key##Up = true;              \
        break;

ExternKeyMapping(Space);

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