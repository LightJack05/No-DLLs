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

void CollisionChecks(GameObject *object)
{
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
        HandleCollision(object, colliderTL, round(nextXPositionTL), round(nextYPositionTL), xPositionTL, yPositionTL);
    }

    if (colliderTR != NULL && !(IsPositionInObject(colliderTR, xPositionTR, yPositionTR)))
    {
        HandleCollision(object, colliderTR, round(nextXPositionTR), round(nextYPositionTR), xPositionTR, yPositionTR);
    }

    if (colliderBL != NULL && !(IsPositionInObject(colliderBL, xPositionBL, yPositionBL)))
    {
        HandleCollision(object, colliderBL, round(nextXPositionBL), round(nextYPositionBL), xPositionBL, yPositionBL);
    }

    if (colliderBR != NULL && !(IsPositionInObject(colliderBR, xPositionBR, yPositionBR)))
    {
        HandleCollision(object, colliderBR, round(nextXPositionBR), round(nextYPositionBR), xPositionBR, yPositionBR);
    }

    SDL_Delay(10);
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

void HandleCollision(GameObject *object, GameObject *collider, int nextCornerPositionX, int nextCornerPositionY, int cornerPositionX, int cornerPositionY)
{
    enum CollisionDirection collisionDirection = RecursivelyGetCollisionDirection(object, collider, nextCornerPositionX, nextCornerPositionY, 1, 1, cornerPositionX, cornerPositionY);
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
        -> caluclate new velocity for both objects
        ---> https://en.wikipedia.org/wiki/Elastic_collision
        ---> include bounciness of both objects
        - Handle bounciness 0?
        */

    case Direction_Bottom:
        printf("Collision from bottom!");
        break;
    case Direction_Top:
        printf("Collision from top!");
        break;
    case Direction_Right:
        printf("Collision from right!");
        break;
    case Direction_Left:
        printf("Collision from left!");
        break;
    case Corner_BL:
        printf("Collision from bottom-left!");
        break;
    case Corner_BR:
        printf("Collision from bottom-right!");
        break;
    case Corner_TL:
        printf("Collision from top-left!");
        break;
    case Corner_TR:
        printf("Collision from top-right!");
        break;

    default:
        break;
    }
}

enum CollisionDirection RecursivelyGetCollisionDirection(GameObject *object, GameObject *collider, int positionX, int positionY, int depth, double currentFactor, int cornerPositionX, int cornerPositionY)
{
    enum CollisionDirection collisionDirection = CheckCollisionDirection(collider, positionX, positionY);

    if (collisionDirection != None)
    {
        return collisionDirection;
    }
    else
    {
        int nextCheckPositionX = 0;
        int nextCheckPositionY = 0;

        if (IsPositionInObject(collider, positionX, positionY))
        {
            currentFactor -= 1.0 / pow(2, depth);
        }
        else
        {
            currentFactor += 1.0 / pow(2, depth);
        }
        depth++;

        nextCheckPositionX = round(cornerPositionX + object->velocity_x * Time_DeltaTime * currentFactor);
        nextCheckPositionY = round(cornerPositionY + object->velocity_y * Time_DeltaTime * currentFactor);

        return RecursivelyGetCollisionDirection(object, collider, nextCheckPositionX, nextCheckPositionY, depth, currentFactor, cornerPositionX, cornerPositionY);
    }
}

enum CollisionDirection CheckCollisionDirection(GameObject *object, int positionX, int positionY)
{
    double objectYPositionTL = object->position_y;
    double objectXPositionTL = object->position_x;

    double objectYPositionTR = objectYPositionTL;
    double objectXPositionTR = objectXPositionTL + object->width;

    double objectYPositionBL = objectYPositionTL + object->height;
    double objectXPositionBL = objectXPositionTL;

    double objectYPositionBR = objectYPositionTL + object->height;
    double objectXPositionBR = objectXPositionTL + object->width;

    if (objectXPositionTL == positionX && objectYPositionTL == positionY)
    {
        return Corner_TL;
    }
    if (objectXPositionTR == positionX && objectYPositionTR == positionY)
    {
        return Corner_TR;
    }
    if (objectXPositionBL == positionX && objectYPositionBL == positionY)
    {
        return Corner_BL;
    }
    if (objectXPositionBR == positionX && objectYPositionBR == positionY)
    {
        return Corner_BR;
    }

    // Right edge
    if (positionX == objectXPositionBR &&
        positionY > objectYPositionTR &&
        positionY < objectYPositionBR)
    {
        return Direction_Right;
    }
    // Left edge
    if (positionX == objectXPositionBL &&
        positionY > objectYPositionTL &&
        positionY < objectYPositionBL)
    {
        return Direction_Left;
    }
    // Top edge
    if (positionY == objectYPositionTR &&
        positionX > objectXPositionTL &&
        positionX < objectXPositionTR)
    {
        return Direction_Top;
    }
    // Bottom edge
    if (positionY == objectYPositionBR &&
        positionX > objectXPositionBL &&
        positionX < objectXPositionBR)
    {
        return Direction_Bottom;
    }
    return None;
}
