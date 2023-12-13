#ifndef CONTROLS_H
#define CONTROLS_H
#include <stdbool.h>

#include "SDL2/SDL.h"

#define ExternKeyMapping(Key)       \
    extern bool Controls_##Key;     \
    extern bool Controls_##Key##Up; \
    extern bool Controls_##Key##Down;

#define KeyMapping(Key)              \
    bool Controls_##Key = false;     \
    bool Controls_##Key##Up = false; \
    bool Controls_##Key##Down = false;

#define KeyMappingReset(Key)    \
    Controls_##Key##Up = false; \
    Controls_##Key##Down = false;

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
ExternKeyMapping(W);
ExternKeyMapping(S);
ExternKeyMapping(A);
ExternKeyMapping(D);

void Controls_KeyDown(SDL_Keycode sym);
void Controls_KeyUp(SDL_Keycode sym);
void ResetKeyUpDown();

#endif // CONTROLS_H