#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

void initializeSDL(SDL_Window **window, SDL_Renderer **renderer);
void cleanupSDL(SDL_Window *window, SDL_Renderer *renderer);
void drawWalls(SDL_Renderer *renderer, double posX, double posY,
               double dirX, double dirY, double planeX, double planeY);
void setCameraAngle(double *dirX, double *dirY, double *planeX, double *planeY, double angle);

#endif /* RAYCASTING_H */

