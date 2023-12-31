#include "objects.h"
#include <stdlib.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "constants.h"
#include "genericLinkedList.h"

struct GenericLinkedList(voidPtr) * gameObjects;

GameObject *NewRectangle()
{
    GameObject *newObject = malloc(sizeof(GameObject));
    SDL_Rect *newObjectObject = malloc(sizeof(SDL_Rect));
    newObject->object = newObjectObject;
    newObject->objectType = Type_SDL_Rect;

    newObjectObject->w = 0;
    newObjectObject->h = 0;

    newObjectObject->x = 0;
    newObjectObject->y = 0;

    newObject->position_x = newObjectObject->x;
    newObject->position_y = newObjectObject->y;

    newObject->width = newObjectObject->w;
    newObject->height = newObjectObject->h;

    newObject->usesGravity = false;
    newObject->gravityScale = 1;
    newObject->isKinematic = false;
    newObject->velocity_x = 0;
    newObject->velocity_y = 0;

    newObject->hasCollider = false;
    newObject->bounciness = 0;
    newObject->mass = 0;

    newObject->blockOtherXBounces = false;
    newObject->blockOtherYBounces = false;

    newObject->respectScreenEdgeBottom = true;
    newObject->respectScreenEdgeTop = true;
    newObject->respectScreenEdgeLeft = true;
    newObject->respectScreenEdgeRight = true;
    newObject->screenEdgeBounciness = 0;

    newObject->color_r = 0;
    newObject->color_b = 0;
    newObject->color_g = 0;

    gameObjects->pushBack(gameObjects, newObject);
    return newObject;
}

void InitObjects()
{
    gameObjects = newGenericLinkedList(voidPtr);
}

void DestroyObject(GameObject *object)
{
    free(object->object);
    int objectIndex = gameObjects->find(gameObjects, object);
    free(object);
    gameObjects->popAt(gameObjects, objectIndex);
}