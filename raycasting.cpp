#include "raycasting.h"
#include <cmath>

/**
 * drawWalls - Draws walls using raycasting
 * @renderer: SDL renderer
 * @posX: Player's x position
 * @posY: Player's y position
 * @dirX: Player's x direction
 * @dirY: Player's y direction
 * @planeX: Camera plane x component
 * @planeY: Camera plane y component
 */
void drawWalls(SDL_Renderer *renderer, double posX, double posY,
		double dirX, double dirY, double planeX, double planeY)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		double cameraX = 2 * x / double(SCREEN_WIDTH) - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeX * cameraX;

		int mapX = int(posX);
		int mapY = int(posY);

		double sideDistX, sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
		double perpWallDist;

		int stepX, stepY;
		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

		SDL_Color color;
		if (side == 0) // North/South walls
		{
			color = (rayDirX > 0) ? SDL_Color{255, 0, 0, 255} : SDL_Color{0, 255, 0, 255};
		}
		else // East/West walls
		{
			color = (rayDirY > 0) ? SDL_Color{0, 0, 255, 255} : SDL_Color{255, 255, 0,

