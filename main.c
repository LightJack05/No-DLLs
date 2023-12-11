#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "controls.h"
#include "objects.h"
#include "movement.h"
#include "time.h"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

void mainLoop(SDL_Window *window, SDL_Renderer *renderer)
{

    player->w = 100;
    player->h = 100;

    player->x = (SCREEN_WIDTH / 2) - (player->w / 2);
    player->y = (SCREEN_HEIGHT / 2) - (player->h / 2);

    bool quit = false;
    while (!quit)
    {
        UpdateDeltaTime();
        printf("%d\n", Time_DeltaTime);
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

        // Initialize renderer color white for the background
        SDL_SetRenderDrawColor(renderer, 0x12, 0x12, 0x12, 0xFF);
        // 181818

        // Clear screen
        SDL_RenderClear(renderer);

        // Set renderer color red to draw the square
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

        SDL_RenderFillRect(renderer, player);

        // Update screen
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
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
