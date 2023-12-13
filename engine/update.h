#ifndef UPDATE_H
#define UPDATE_H
#include "SDL2/SDL.h"
#include "objects.h"

void UpdateRenderer(SDL_Renderer *renderer);
void UpdateSpritePositionsFromGameObjects();
void KinematicTick(GameObject *currentGameObject);
void GravityTick(GameObject *currentGameObject);
#endif // UPDATE_H