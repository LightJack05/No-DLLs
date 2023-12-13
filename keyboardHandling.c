#include "keyboardHandling.h"
#include "SDL2/SDL.h"

KeyMapping(Space);
KeyMapping(W);
KeyMapping(S);
KeyMapping(A);
KeyMapping(D);

void Controls_KeyDown(SDL_Keycode keycode)
{
    switch (keycode)
    {
        KeyMappingSwitchCaseDown(W, SDLK_w);
        KeyMappingSwitchCaseDown(S, SDLK_s);
        KeyMappingSwitchCaseDown(A, SDLK_a);
        KeyMappingSwitchCaseDown(D, SDLK_d);
        KeyMappingSwitchCaseDown(Space, SDLK_SPACE);
    default:
        break;
    }
}
void Controls_KeyUp(SDL_Keycode keycode)
{
    switch (keycode)
    {
        KeyMappingSwitchCaseUp(W, SDLK_w);
        KeyMappingSwitchCaseUp(S, SDLK_s);
        KeyMappingSwitchCaseUp(A, SDLK_a);
        KeyMappingSwitchCaseUp(D, SDLK_d);
        KeyMappingSwitchCaseUp(Space, SDLK_SPACE);
    default:
        break;
    }
}

void ResetKeyUpDown()
{
    KeyMappingReset(Space);
    KeyMappingReset(W);
    KeyMappingReset(S);
    KeyMappingReset(A);
    KeyMappingReset(D);
}