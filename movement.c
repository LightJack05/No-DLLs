#include "movement.h"
#include "keyboardHandling.h"
#include "objects.h"
#include "time.h"

void ControlTick()
{
    if (Controls_SUp)
    {
        DestroyObject(player);
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