#include "controls.h"
#include "SDL2/SDL.h"

bool Controls_W = false;
bool Controls_S = false;
bool Controls_A = false;
bool Controls_D = false;

bool Controls_WUp = false;
bool Controls_SUp = false;
bool Controls_AUp = false;
bool Controls_DUp = false;

bool Controls_WDown = false;
bool Controls_SDown = false;
bool Controls_ADown = false;
bool Controls_DDown = false;

void Controls_KeyDown(SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_w:
        Controls_W = true;
        Controls_WDown = true;
        Controls_WUp = false;
        break;
    case SDLK_s:
        Controls_SDown = true;
        Controls_S = true;
        Controls_SUp = false;
        break;
    case SDLK_a:
        Controls_ADown = true;
        Controls_A = true;
        Controls_AUp = false;
        break;
    case SDLK_d:
        Controls_DDown = true;
        Controls_D = true;
        Controls_DUp = false;
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
        Controls_WUp = true;
        Controls_W = false;
        Controls_WDown = false;
        break;
    case SDLK_s:
        Controls_SUp = true;
        Controls_S = false;
        Controls_SDown = false;
        break;
    case SDLK_a:
        Controls_AUp = true;
        Controls_A = false;
        Controls_ADown = false;
        break;
    case SDLK_d:
        Controls_DUp = true;
        Controls_D = false;
        Controls_DDown = false;
        break;
    default:
        break;
    }
}

void ResetKeyUpDown()
{
    Controls_WUp = false;
    Controls_SUp = false;
    Controls_AUp = false;
    Controls_DUp = false;

    Controls_WDown = false;
    Controls_SDown = false;
    Controls_ADown = false;
    Controls_DDown = false;
}