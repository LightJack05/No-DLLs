#include "movement.h"
#include "controls.h"
#include "objects.h"
#include "time.h"

void MovementTick()
{
    if (Controls_DDown)
    {
        player->x += 1 * Time_DeltaTime;
    }
    if (Controls_WDown)
    {
        player->y -= 1 * Time_DeltaTime;
    }
    if (Controls_SDown)
    {
        player->y += 1 * Time_DeltaTime;
    }
    if (Controls_ADown)
    {
        player->x -= 1 * Time_DeltaTime;
    }
}