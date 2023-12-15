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

    player->width = 20.0;
    player->height = 20.0;

    player->position_x = 100.0;
    player->position_y = 120.0;

    player->usesGravity = false;
    player->isKinematic = true;
    player->hasCollider = true;

    player->velocity_x = 0.01;
    player->velocity_y = 0.0;

    player->color_r = 255;
}

void CreateFloor()
{
    GameObject *collider = NewRectangle();
    collider->hasCollider = true;
    collider->isKinematic = true;
    collider->color_b = 255;
    collider->width = 20.0;
    collider->height = 80.0;
    collider->position_x = 145.0;
    collider->position_y = 125.0;
    collider->velocity_x = -0.005;
    collider->velocity_y = 0.0;
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