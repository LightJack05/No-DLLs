#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "controls.h"
#include "objects.h"
#include "movement.h"
#include "time.h"
#include "update.h"
#include "constants.h"
#include "genericLinkedList.h"

void mainLoop(SDL_Window *window, SDL_Renderer *renderer)
{

    bool quit = false;
    while (!quit)
    {

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                Controls_KeyDown(e.key.keysym.sym);
            }
            else if (e.type == SDL_KEYUP)
            {
                Controls_KeyUp(e.key.keysym.sym);
            }
        }
        MovementTick();
        UpdateRenderer(renderer);
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("No-DLLs",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (window)
    {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer)
        {
            initObjects();
            mainLoop(window, renderer);
            SDL_DestroyRenderer(renderer);
        }
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}
