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

    player->width = 20;
    player->height = 20;

    player->position_x = 100;
    player->position_y = 100;

    player->usesGravity = false;
    player->isKinematic = true;
    player->hasCollider = true;

    player->velocity_x = 0.001;
    player->velocity_y = 0.001;

    player->color_r = 255;
}

void CreateFloor()
{
    GameObject *collider = NewRectangle();
    collider->hasCollider = true;
    collider->color_b = 255;
    collider->width = 20;
    collider->height = 20;
    collider->position_x = 130;
    collider->position_y = 130;
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