#include "movement.h"
#include "keyboardHandling.h"
#include "objects.h"
#include "time.h"

void ControlTick()
{
    if (Controls_SUp)
    {
        for (int i = 0; i < 20000; i++)
        {
            GameObject *someNewRectangle = newRectangle();
            someNewRectangle->width = 100;
            someNewRectangle->height = 150;

            someNewRectangle->color_b = 255;
        }

        for (int i = gameObjects->Length - 1; i > 0; i--)
        {
            DestroyObject(gameObjects->at(gameObjects, i));
        }
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