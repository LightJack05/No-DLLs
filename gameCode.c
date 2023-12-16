#include "gameCode.h"
#include "engine/constants.h"
#include "SDL2/SDL.h"
#include "engine/objects.h"
#include "engine/keyboardHandling.h"
#include "engine/constants.h"

GameObject *player;

void Start()
{
    InitPlayer();
    CreateFloor();
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

    player->usesGravity = false;
    player->isKinematic = true;
    player->hasCollider = true;
    player->bounciness = 1;
    player->screenEdgeBounciness = 1.1;
    player->mass = 5;

    player->velocity_x = 0;
    player->velocity_y = -0.3;

    player->color_r = 255;
}

void CreateFloor()
{
    GameObject *collider = NewRectangle();
    collider->hasCollider = true;
    collider->isKinematic = true;
    collider->color_b = 255;
    collider->width = 40;
    collider->height = 40;
    collider->position_x = 800;
    collider->position_y = 200;
    collider->velocity_x = 0;
    collider->velocity_y = 0;
    collider->bounciness = 1;
    collider->screenEdgeBounciness = 1;
    collider->mass = 5;
}

void ControlMovements()
{
    if (Controls_SUp)
    {
    }

    if (Controls_D)
    {
        player->velocity_x = 0.5;
    }
    if (Controls_DUp)
    {
        player->velocity_x = 0;
    }

    if (Controls_WDown || Controls_SpaceDown)
    {
        player->velocity_y = -0.5;
    }

    if (Controls_A)
    {
        player->velocity_x = -0.5;
    }
    if (Controls_AUp)
    {
        player->velocity_x = 0;
    }
}