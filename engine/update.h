#ifndef UPDATE_H
#define UPDATE_H
#include "SDL2/SDL.h"
#include "objects.h"

void UpdateRenderer(SDL_Renderer *renderer);
void UpdateSpritePositionsFromGameObjects();
void KinematicTick(GameObject *currentGameObject);
void GravityTick(GameObject *currentGameObject);
void CollisionChecks(GameObject *object);
GameObject *GetCollider(GameObject *collidingObject, double xPosition, double yPosition);
bool IsPositionInObject(GameObject *collider, double positionX, double positionY);
void HandleCollision(GameObject *object, GameObject *collider, double nextCornerPositionX, double nextCornerPositionY, double cornerPositionX, double cornerPositionY);

enum CollisionDirection RecursivelyGetCollisionDirection(GameObject *object, GameObject *collider, double positionX, double positionY, int depth, double currentFactor, double cornerPositionX, double cornerPositionY);

enum CollisionDirection CheckCollisionDirection(GameObject *object, int positionX, int positionY);

enum CollisionDirection
{
    Direction_Top,
    Direction_Bottom,
    Direction_Left,
    Direction_Right,
    Corner_TL,
    Corner_TR,
    Corner_BL,
    Corner_BR,
    None
};

#endif // UPDATE_H