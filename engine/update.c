#include <stdio.h>
#include "update.h"
#include "SDL2/SDL.h"
#include "objects.h"
#include "time.h"
#include "math.h"
#include "constants.h"

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
}

void UpdateSpritePositionsFromGameObjects()
{
    for (int i = 0; i < gameObjects->Length; i++)
    {
        GameObjectPtr currentGameObject = ((GameObjectPtr)(gameObjects->at(gameObjects, i)));
        GravityTick(currentGameObject);
        KinematicTick(currentGameObject);

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

void GravityTick(GameObject *currentGameObject)
{
    if (currentGameObject->usesGravity && currentGameObject->isKinematic)
    {
        currentGameObject->velocity_y += 0.001 * Time_DeltaTime * currentGameObject->gravityScale;
    }
}

void KinematicTick(GameObject *currentGameObject)
{
    if (currentGameObject->isKinematic)
    {

        double nextYPosition = currentGameObject->position_y + currentGameObject->velocity_y * Time_DeltaTime;
        double nextXPosition = currentGameObject->position_x + currentGameObject->velocity_x * Time_DeltaTime;

        if ((nextXPosition > (SCREEN_WIDTH - (currentGameObject->width))) && currentGameObject->respectScreenEdgeRight)
        {
            currentGameObject->position_x = SCREEN_WIDTH - (currentGameObject->width);
            currentGameObject->velocity_x = 0;
        }
        else if (nextXPosition < 0 && currentGameObject->respectScreenEdgeLeft)
        {
            currentGameObject->position_x = 0;
            currentGameObject->velocity_x = 0;
        }
        else
        {
            currentGameObject->position_x = nextXPosition;
        }

        if ((nextYPosition > (SCREEN_HEIGHT - (currentGameObject->height))) && currentGameObject->respectScreenEdgeBottom)
        {
            currentGameObject->position_y = SCREEN_HEIGHT - (currentGameObject->height);
            currentGameObject->velocity_y = 0;
        }
        else if (nextYPosition < 0 && currentGameObject->respectScreenEdgeTop)
        {
            currentGameObject->position_y = 0;
            currentGameObject->velocity_y = 0;
        }
        else
        {
            currentGameObject->position_y = nextYPosition;
        }
    }
}