#include "gameCode.h"
#include "engine/constants.h"
#include "SDL2/SDL.h"
#include "engine/objects.h"
#include "engine/keyboardHandling.h"

GameObject *player;

void Start()
{
    InitPlayer();
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

    player->position_x = (SCREEN_WIDTH / 2) - (player->width / 2);
    player->position_y = 40;

    player->usesGravity = true;
    player->isKinematic = true;

    player->color_r = 255;
    player->color_b = 0;
    player->color_g = 0;
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