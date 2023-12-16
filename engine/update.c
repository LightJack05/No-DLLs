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
        CollisionChecks(currentGameObject);
    }

    for (int i = 0; i < gameObjects->Length; i++)
    {
        GameObjectPtr currentGameObject = ((GameObjectPtr)(gameObjects->at(gameObjects, i)));
        currentGameObject->blockOtherXBounces = false;
        currentGameObject->blockOtherYBounces = false;
    }

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
            currentGameObject->blockOtherXBounces = true;
            currentGameObject->position_x = (SCREEN_WIDTH - (currentGameObject->width));
            currentGameObject->velocity_x = -(fabs(currentGameObject->velocity_x)) * (currentGameObject->screenEdgeBounciness);
        }
        else if (nextXPosition < 0 && currentGameObject->respectScreenEdgeLeft)
        {
            currentGameObject->blockOtherXBounces = true;
            currentGameObject->position_x = 0;
            currentGameObject->velocity_x = (fabs(currentGameObject->velocity_x)) * (currentGameObject->screenEdgeBounciness);
        }
        else
        {
            currentGameObject->position_x = nextXPosition;
        }

        if ((nextYPosition > (SCREEN_HEIGHT - (currentGameObject->height))) && currentGameObject->respectScreenEdgeBottom)
        {
            currentGameObject->position_y = SCREEN_HEIGHT - (currentGameObject->height);
            currentGameObject->blockOtherYBounces = true;
            currentGameObject->velocity_y = -(fabs(currentGameObject->velocity_y)) * (currentGameObject->screenEdgeBounciness);
        }
        else if (nextYPosition < 0 && currentGameObject->respectScreenEdgeTop)
        {
            currentGameObject->position_y = 0;
            currentGameObject->blockOtherYBounces = true;
            currentGameObject->velocity_y = (fabs(currentGameObject->velocity_y)) * (currentGameObject->screenEdgeBounciness);
        }
        else
        {
            currentGameObject->position_y = nextYPosition;
        }
    }
}

void CollisionChecks(GameObject *object)
{
    if (object->isKinematic == false || (object->velocity_x == 0 && object->velocity_y == 0))
    {
        return;
    }
    double nextYPositionTL = object->position_y + object->velocity_y * Time_DeltaTime;
    double nextXPositionTL = object->position_x + object->velocity_x * Time_DeltaTime;

    double nextYPositionTR = nextYPositionTL;
    double nextXPositionTR = nextXPositionTL + object->width;

    double nextYPositionBL = nextYPositionTL + object->height;
    double nextXPositionBL = nextXPositionTL;

    double nextYPositionBR = nextYPositionTL + object->height;
    double nextXPositionBR = nextXPositionTL + object->width;

    double yPositionTL = object->position_y;
    double xPositionTL = object->position_x;

    double yPositionTR = yPositionTL;
    double xPositionTR = xPositionTL + object->width;

    double yPositionBL = yPositionTL + object->height;
    double xPositionBL = xPositionTL;

    double yPositionBR = yPositionTL + object->height;
    double xPositionBR = xPositionTL + object->width;

    GameObject *colliderTL = GetCollider(object, nextXPositionTL, nextYPositionTL);
    GameObject *colliderTR = GetCollider(object, nextXPositionTR, nextYPositionTR);
    GameObject *colliderBL = GetCollider(object, nextXPositionBL, nextYPositionBL);
    GameObject *colliderBR = GetCollider(object, nextXPositionBR, nextYPositionBR);

    if (colliderTL != NULL && !(IsPositionInObject(colliderTL, xPositionTL, yPositionTL)))
    {
        HandleCollision(object, colliderTL, nextXPositionTL, nextYPositionTL, xPositionTL, yPositionTL);
    }

    if (colliderTR != NULL && !(IsPositionInObject(colliderTR, xPositionTR, yPositionTR)))
    {
        HandleCollision(object, colliderTR, nextXPositionTR, nextYPositionTR, xPositionTR, yPositionTR);
    }

    if (colliderBL != NULL && !(IsPositionInObject(colliderBL, xPositionBL, yPositionBL)))
    {
        HandleCollision(object, colliderBL, nextXPositionBL, nextYPositionBL, xPositionBL, yPositionBL);
    }

    if (colliderBR != NULL && !(IsPositionInObject(colliderBR, xPositionBR, yPositionBR)))
    {
        HandleCollision(object, colliderBR, nextXPositionBR, nextYPositionBR, xPositionBR, yPositionBR);
    }
}

GameObject *GetCollider(GameObject *collidingObject, double xPosition, double yPosition)
{
    for (int i = 0; i < gameObjects->Length; i++)
    {
        GameObject *possibleColliderObject = gameObjects->at(gameObjects, i);
        if (possibleColliderObject == collidingObject)
        {
            continue;
        }
        if (IsPositionInObject(possibleColliderObject, xPosition, yPosition))
        {
            return possibleColliderObject;
        }
    }
    return NULL;
}

bool IsPositionInObject(GameObject *collider, double positionX, double positionY)
{
    double colliderBoundaryTop = collider->position_y;
    double colliderBoundaryLeft = collider->position_x;
    double colliderBoundaryRight = colliderBoundaryLeft + collider->width - 1;
    double colliderBoundaryBottom = colliderBoundaryTop + collider->height - 1;

    if (colliderBoundaryLeft <= positionX &&
        positionX <= colliderBoundaryRight &&
        colliderBoundaryTop <= positionY &&
        positionY <= colliderBoundaryBottom)
    {
        return true;
    }
    return false;
}

void HandleCollision(GameObject *object, GameObject *collider, double nextCornerPositionX, double nextCornerPositionY, double cornerPositionX, double cornerPositionY)
{
    enum CollisionDirection collisionDirection = RecursivelyGetCollisionDirection(object, collider, nextCornerPositionX, nextCornerPositionY, 1, 1, cornerPositionX, cornerPositionY);
    UpdateVelocitiesAfterCollision(object, collider, collisionDirection);

    switch (collisionDirection)
    {

        /*
        Elastic collisions:
        - Add mass property
        - Add bounciess property
        - Add mass/surface area to gravity function (drag)
        - if other collider is not kinematic
        -> invert velocity vector
        - else
        -> calculate new velocity for both objects
        ---> https://en.wikipedia.org/wiki/Elastic_collision
        ---> include bounciness of both objects
        - Handle bounciness 0?
        */

    case Direction_Bottom:
        printf("Collision from bottom!\n");
        break;
    case Direction_Top:
        printf("Collision from top!\n");
        break;
    case Direction_Right:
        printf("Collision from right!\n");
        break;
    case Direction_Left:
        printf("Collision from left!\n");
        break;
    case Corner_BL:
        printf("Collision from bottom-left!\n");
        break;
    case Corner_BR:
        printf("Collision from bottom-right!\n");
        break;
    case Corner_TL:
        printf("Collision from top-left!\n");
        break;
    case Corner_TR:
        printf("Collision from top-right!\n");
        break;
    case None:
        printf("Clip!");
        break;
    default:
        break;
    }
}

enum CollisionDirection RecursivelyGetCollisionDirection(GameObject *object, GameObject *collider, double positionX, double positionY, int depth, double currentFactor, double cornerPositionX, double cornerPositionY)
{
    enum CollisionDirection collisionDirection = CheckCollisionDirection(collider, round(positionX), round(positionY));
    if (depth > 1000)
    {
        return None;
    }

    if (collisionDirection != None)
    {
        return collisionDirection;
    }
    else
    {
        double nextCheckPositionX = 0;
        double nextCheckPositionY = 0;

        if (IsPositionInObject(collider, positionX, positionY))
        {
            currentFactor -= 1.0 / pow(2, depth);
        }
        else
        {
            currentFactor += 1.0 / pow(2, depth);
        }
        depth++;

        nextCheckPositionX = cornerPositionX + object->velocity_x * Time_DeltaTime * currentFactor;
        nextCheckPositionY = cornerPositionY + object->velocity_y * Time_DeltaTime * currentFactor;

        return RecursivelyGetCollisionDirection(object, collider, nextCheckPositionX, nextCheckPositionY, depth, currentFactor, cornerPositionX, cornerPositionY);
    }
}

enum CollisionDirection CheckCollisionDirection(GameObject *object, int positionX, int positionY)
{
    double objectYPositionTL = object->position_y;
    double objectXPositionTL = object->position_x;

    double objectYPositionTR = objectYPositionTL;
    double objectXPositionTR = objectXPositionTL + object->width - 1;

    double objectYPositionBL = objectYPositionTL + object->height - 1;
    double objectXPositionBL = objectXPositionTL;

    double objectYPositionBR = objectYPositionTL + object->height - 1;
    double objectXPositionBR = objectXPositionTL + object->width - 1;

    if (round(objectXPositionTL) == positionX && round(objectYPositionTL) == positionY)
    {
        return Corner_TL;
    }
    if (round(objectXPositionTR) == positionX && round(objectYPositionTR) == positionY)
    {
        return Corner_TR;
    }
    if (round(objectXPositionBL) == positionX && round(objectYPositionBL) == positionY)
    {
        return Corner_BL;
    }
    if (round(objectXPositionBR) == positionX && round(objectYPositionBR) == positionY)
    {
        return Corner_BR;
    }

    // Right edge
    if (positionX == round(objectXPositionBR) &&
        positionY > objectYPositionTR &&
        positionY < objectYPositionBR)
    {
        return Direction_Right;
    }
    // Left edge
    if (positionX == round(objectXPositionBL) &&
        positionY > objectYPositionTL &&
        positionY < objectYPositionBL)
    {
        return Direction_Left;
    }
    // Top edge
    if (positionY == round(objectYPositionTR) &&
        positionX > objectXPositionTL &&
        positionX < objectXPositionTR)
    {
        return Direction_Top;
    }
    // Bottom edge
    if (positionY == round(objectYPositionBR) &&
        positionX > objectXPositionBL &&
        positionX < objectXPositionBR)
    {
        return Direction_Bottom;
    }
    return None;
}

void UpdateVelocitiesAfterCollision(GameObject *objectOne, GameObject *objectTwo, CollisionDirection direction)
{
    if (objectOne->isKinematic == false)
    {
        UpdateVelocitiesAfterNonKinematicCollision(objectTwo, objectOne, direction);
    }
    if (objectTwo->isKinematic == false)
    {
        UpdateVelocitiesAfterNonKinematicCollision(objectOne, objectTwo, direction);
    }
    if (objectOne->isKinematic == true && objectTwo->isKinematic == true)
    {
        ElasticCollision(objectOne, objectTwo, direction);
    }
}

void ElasticCollision(GameObject *objectOne, GameObject *objectTwo, CollisionDirection direction)
{
    switch (direction)
    {
    case Direction_Bottom:
    case Direction_Top:
        if (!(objectOne->blockOtherXBounces || objectTwo->blockOtherXBounces))
        {
            UpdateVelocitiesAfterElasticCollision(&(objectOne->velocity_y), &(objectTwo->velocity_y), objectOne->mass, objectTwo->mass);
            objectOne->blockOtherXBounces = true;
            objectTwo->blockOtherXBounces = true;
        }
        break;
    case Direction_Right:
    case Direction_Left:
        if (!(objectOne->blockOtherYBounces || objectTwo->blockOtherYBounces))
        {
            UpdateVelocitiesAfterElasticCollision(&(objectOne->velocity_x), &(objectTwo->velocity_x), objectOne->mass, objectTwo->mass);
            objectOne->blockOtherXBounces = true;
            objectTwo->blockOtherXBounces = true;
        }
        break;
    case Corner_BL:
    case Corner_BR:
    case Corner_TL:
    case Corner_TR:
        if (!(objectOne->blockOtherXBounces || objectTwo->blockOtherXBounces))
        {
            UpdateVelocitiesAfterElasticCollision(&(objectOne->velocity_y), &(objectTwo->velocity_y), objectOne->mass, objectTwo->mass);
        }
        if (!(objectOne->blockOtherYBounces || objectTwo->blockOtherYBounces))
        {
            UpdateVelocitiesAfterElasticCollision(&(objectOne->velocity_x), &(objectTwo->velocity_x), objectOne->mass, objectTwo->mass);
        }
        objectOne->blockOtherXBounces = true;
        objectTwo->blockOtherXBounces = true;
        break;

    default:
        break;
    }
}

void UpdateVelocitiesAfterElasticCollision(double *relevantVelocityOne, double *relevantVelocityTwo, double massOne, double massTwo)
{
    double oldVelocityOne = *relevantVelocityOne;
    double oldVelocityTwo = *relevantVelocityTwo;

    *relevantVelocityOne = (((massOne - massTwo) / (massOne + massTwo)) * oldVelocityOne) + (((2 * massTwo) / (massOne + massTwo)) * oldVelocityTwo);

    *relevantVelocityTwo = (((2 * massOne) / (massOne + massTwo)) * oldVelocityOne) + (((massTwo - massOne) / (massOne + massTwo)) * oldVelocityTwo);
}

void UpdateVelocitiesAfterNonKinematicCollision(GameObject *object, GameObject *staticObject, CollisionDirection direction)
{
    switch (direction)
    {
    case Direction_Bottom:
    case Direction_Top:
        BounceYVelocity(object, staticObject);
        break;
    case Direction_Right:
    case Direction_Left:
        BounceXVelocity(object, staticObject);
        break;
    case Corner_BL:
    case Corner_BR:
    case Corner_TL:
    case Corner_TR:
        BounceYVelocity(object, staticObject);
        BounceXVelocity(object, staticObject);
        break;

    default:
        break;
    }
}

void BounceXVelocity(GameObject *object, GameObject *staticObject)
{
    if (!(object->blockOtherXBounces))
    {
        object->blockOtherXBounces = true;
        object->velocity_x = -(object->velocity_x) * ((object->bounciness + staticObject->bounciness) / 2);
    }
}

void BounceYVelocity(GameObject *object, GameObject *staticObject)
{
    if (!(object->blockOtherYBounces))
    {
        object->blockOtherYBounces = true;
        object->velocity_y = -(object->velocity_y) * ((object->bounciness + staticObject->bounciness) / 2);
    }
}
