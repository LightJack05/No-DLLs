#include <stdio.h>
#include "update.h"
#include "SDL2/SDL.h"
#include "objects.h"
#include "movement.h"
#include "time.h"
#include "math.h"

void UpdateRenderer(SDL_Renderer *renderer)
{
    UpdateDeltaTime();
    UpdateSpritePositionsFromGameObjects();
    printf("%d\n", Time_DeltaTime);
    // Initialize renderer color white for the background
    SDL_SetRenderDrawColor(renderer, 0x12, 0x12, 0x12, 0xFF);
    // 181818

    // Clear screen
    SDL_RenderClear(renderer);

    for (int i = 0; i < gameObjects->Length; i++)
    {
        GameObjectPtr currentGameObject = ((GameObjectPtr)(gameObjects->at(gameObjects, i)));

        switch (currentGameObject->objectType)
        {
        case 0:
            SDL_SetRenderDrawColor(renderer, currentGameObject->color_r, currentGameObject->color_g, currentGameObject->color_b, 0xFF);
            SDL_RenderFillRect(renderer, currentGameObject->object);
            break;

        default:
            break;
        }
    }

    // // Set renderer color red to draw the square
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

    // SDL_RenderFillRect(renderer, player);

    // Update screen
    SDL_RenderPresent(renderer);

    SDL_Delay(10);
}

void UpdateSpritePositionsFromGameObjects()
{
    for (int i = 0; i < gameObjects->Length; i++)
    {
        GameObjectPtr currentGameObject = ((GameObjectPtr)(gameObjects->at(gameObjects, i)));

        switch (currentGameObject->objectType)
        {
        case 0:
            SDL_Rect *rectangle = currentGameObject->object;
            rectangle->x = round(currentGameObject->position_x);
            rectangle->y = round(currentGameObject->position_y);

            rectangle->w = round(currentGameObject->width);
            rectangle->h = round(currentGameObject->height);
            break;

        default:
            break;
        }
    }
}