#include "movement.h"
#include "controls.h"
#include "objects.h"
#include "time.h"

void MovementTick()
{

    if (Controls_DDown)
    {
        player->position_x += 1 * Time_DeltaTime;
    }
    if (Controls_WDown)
    {
        player->position_y -= 1 * Time_DeltaTime;
    }
    if (Controls_SDown)
    {
        player->position_y += 1 * Time_DeltaTime;
    }
    if (Controls_ADown)
    {
        player->position_x -= 1 * Time_DeltaTime;
    }
}