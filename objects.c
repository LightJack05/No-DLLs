#include "objects.h"
#include <stdlib.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "constants.h"
#include "genericLinkedList.h"

GameObject *player;

struct GenericLinkedList(voidPtr) * gameObjects;

void initObjects()
{
    gameObjects = newGenericLinkedList(voidPtr);

    initPlayer();
}

void initPlayer()
{
    player = malloc(sizeof(GameObject));
    SDL_Rect *playerRectangle = malloc(sizeof(SDL_Rect));
    player->object = playerRectangle;
    player->objectType = Rectangle;

    playerRectangle->w = 100;
    playerRectangle->h = 100;

    playerRectangle->x = (SCREEN_WIDTH / 2) - (playerRectangle->w / 2);
    playerRectangle->y = (SCREEN_HEIGHT / 2) - (playerRectangle->h / 2);

    player->position_x = playerRectangle->x;
    player->position_y = playerRectangle->y;

    player->width = playerRectangle->w;
    player->height = playerRectangle->h;

    player->usesGravity = false;
    player->isKinematic = false;

    player->color_r = 255;
    player->color_b = 0;
    player->color_g = 0;

    gameObjects->pushBack(gameObjects, player);
}