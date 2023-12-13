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
    initializeObjectHeap(player, SDL_Rect);

    player->width = 20;
    player->height = 20;

    player->position_x = (SCREEN_WIDTH / 2) - (player->width / 2);
    player->position_y = 40;

    player->usesGravity = true;
    player->isKinematic = true;

    player->color_r = 255;
    player->color_b = 0;
    player->color_g = 0;
}

void DestroyObject(GameObject *object)
{
    free(object->object);
    gameObjects->popAt(gameObjects, gameObjects->find(gameObjects, object));
    free(object);
}