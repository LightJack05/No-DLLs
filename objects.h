#ifndef OBJECTS_H
#define OBJECTS_H
#include "SDL2/SDL.h"
#include <stdbool.h>
#include "genericLinkedList.h"

extern struct GenericLinkedListvoidPtr *gameObjects;

typedef struct gameObject GameObject;

extern GameObject *player;

enum ObjectType
{
    Rectangle
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

#endif // OBJECTS_H