#include "gameCode.h"
#include "engine/constants.h"
#include "SDL2/SDL.h"
#include "engine/objects.h"
#include "engine/keyboardHandling.h"
#include "engine/constants.h"

GameObject *player;

void Start()
{
    // InitPlayer();
    for (int i = 0; i < 10; i++)
    {
        CreateRubberBall();
    }
}

/// @brief Update will run every Frame.
void Update()
{
    ControlMovements();
}

void InitPlayer()
{
    player = NewRectangle();

    player->width = 40.0;
    player->height = 40.0;

    player->position_x = 800;
    player->position_y = 1000;

    player->usesGravity = true;
    player->isKinematic = true;
    player->hasCollider = true;
    player->bounciness = 1;
    player->screenEdgeBounciness = 1;
    player->mass = 5;

    player->velocity_x = 0;
    player->velocity_y = -0.3;

    player->color_r = 255;
}

void CreateRubberBall()
{
    GameObject *collider = NewRectangle();
    collider->usesGravity = true;
    collider->hasCollider = true;
    collider->isKinematic = true;
    collider->color_b = 255;
    collider->width = 40;
    collider->height = 40;
    collider->position_x = rand() % 800;
    collider->position_y = rand() % 800;
    collider->velocity_x = (rand() % 1000) / (double)1000;
    collider->velocity_y = (rand() % 1000) / (double)1000;
    collider->bounciness = 1;
    collider->screenEdgeBounciness = 1;
    collider->mass = 5;
}

void ControlMovements()
{
    if (Controls_SUp)
    {
    }

    if (Controls_DDown)
    {
        player->velocity_x += 0.5;
    }
    if (Controls_DUp)
    {
    }

    if (Controls_WDown || Controls_SpaceDown)
    {
        player->velocity_y += -0.5;
    }

    if (Controls_ADown)
    {
        player->velocity_x += -0.5;
    }
    if (Controls_AUp)
    {
    }
}