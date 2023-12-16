#ifndef UPDATE_H
#define UPDATE_H
#include "SDL2/SDL.h"
#include "objects.h"

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

typedef enum CollisionDirection CollisionDirection;

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

void UpdateVelocitiesAfterCollision(GameObject *objectOne, GameObject *objectTwo, CollisionDirection direction);

void ElasticCollision(GameObject *objectOne, GameObject *objectTwo, CollisionDirection direction);

void UpdateVelocitiesAfterElasticCollision(double *relevantVelocityOne, double *relevantVelocityTwo, double massOne, double massTwo);

void UpdateVelocitiesAfterNonKinematicCollision(GameObject *object, GameObject *staticObject, CollisionDirection direction);

void BounceXVelocity(GameObject *object, GameObject *staticObject);

void BounceYVelocity(GameObject *object, GameObject *staticObject);

#endif // UPDATE_H