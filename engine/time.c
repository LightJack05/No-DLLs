#include "time.h"
#include "SDL2/SDL.h"

unsigned int Time_DeltaTime = 1;
unsigned int lastFrameTime = 0;

void UpdateDeltaTime()
{
    unsigned int currentFrameTime = SDL_GetTicks();
    Time_DeltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}