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

    playerRectangle->w = 20;
    playerRectangle->h = 20;

    playerRectangle->x = (SCREEN_WIDTH / 2) - (playerRectangle->w / 2);
    playerRectangle->y = 40;

    player->position_x = playerRectangle->x;
    player->position_y = playerRectangle->y;

    player->width = playerRectangle->w;
    player->height = playerRectangle->h;

    player->usesGravity = true;
    player->gravityScale = 1;
    player->isKinematic = true;
    player->velocity_x = 0;
    player->velocity_y = 0;

    player->respectScreenEdgeBottom = true;
    player->respectScreenEdgeTop = true;
    player->respectScreenEdgeLeft = true;
    player->respectScreenEdgeRight = true;

    player->color_r = 255;
    player->color_b = 0;
    player->color_g = 0;

    gameObjects->pushBack(gameObjects, player);
}