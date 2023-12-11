#include "controls.h"
#include "SDL2/SDL.h"

bool Controls_WDown = false;
bool Controls_SDown = false;
bool Controls_ADown = false;
bool Controls_DDown = false;

void Controls_KeyDown(SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_w:
        Controls_WDown = true;
        break;
    case SDLK_s:
        Controls_SDown = true;
        break;
    case SDLK_a:
        Controls_ADown = true;
        break;
    case SDLK_d:
        Controls_DDown = true;
        break;
    default:
        break;
    }
}
void Controls_KeyUp(SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_w:
        Controls_WDown = false;
        break;
    case SDLK_s:
        Controls_SDown = false;
        break;
    case SDLK_a:
        Controls_ADown = false;
        break;
    case SDLK_d:
        Controls_DDown = false;
        break;
    default:
        break;
    }
}