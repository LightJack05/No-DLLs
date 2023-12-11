#include "objects.h"
#include <stdlib.h>
#include "SDL2/SDL.h"

SDL_Rect *player;

void initObjects()
{
    player = malloc(sizeof(SDL_Rect));
}