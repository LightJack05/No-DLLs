#ifndef OBJECTS_H
#define OBJECTS_H
#include "SDL2/SDL.h"
#include <stdbool.h>
#include "genericLinkedList.h"

#define initializeObjectHeap(objectName, _objectType)                \
    objectName = malloc(sizeof(GameObject));                         \
    SDL_Rect *objectName##_objectType = malloc(sizeof(_objectType)); \
    objectName->object = objectName##_objectType;                    \
    objectName->objectType = Type_##_objectType;                     \
                                                                     \
    objectName##_objectType->w = 0;                                  \
    objectName##_objectType->h = 0;                                  \
                                                                     \
    objectName##_objectType->x = 0;                                  \
    objectName##_objectType->y = 0;                                  \
                                                                     \
    objectName->position_x = objectName##_objectType->x;             \
    objectName->position_y = objectName##_objectType->y;             \
                                                                     \
    objectName->width = objectName##_objectType->w;                  \
    objectName->height = objectName##_objectType->h;                 \
                                                                     \
    objectName->usesGravity = false;                                 \
    objectName->gravityScale = 1;                                    \
    objectName->isKinematic = false;                                 \
    objectName->velocity_x = 0;                                      \
    objectName->velocity_y = 0;                                      \
                                                                     \
    objectName->respectScreenEdgeBottom = true;                      \
    objectName->respectScreenEdgeTop = true;                         \
    objectName->respectScreenEdgeLeft = true;                        \
    objectName->respectScreenEdgeRight = true;                       \
                                                                     \
    objectName->color_r = 0;                                         \
    objectName->color_b = 0;                                         \
    objectName->color_g = 0;                                         \
                                                                     \
    gameObjects->pushBack(gameObjects, objectName);

extern struct GenericLinkedListvoidPtr *gameObjects;

typedef struct gameObject GameObject;

extern GameObject *player;

enum ObjectType
{
    Type_SDL_Rect
};

struct gameObject
{
    double position_x;
    double position_y;
    double width;
    double height;

    bool usesGravity;
    double gravityScale;

    bool isKinematic;
    double velocity_x;
    double velocity_y;

    unsigned char color_r;
    unsigned char color_g;
    unsigned char color_b;

    bool respectScreenEdgeBottom;
    bool respectScreenEdgeTop;
    bool respectScreenEdgeRight;
    bool respectScreenEdgeLeft;

    enum ObjectType objectType;

    void *object;
};

typedef GameObject *GameObjectPtr;

void initObjects();
void initPlayer();
void DestroyObject(GameObject *object);

#endif // OBJECTS_H