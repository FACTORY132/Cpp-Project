#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_image.h>
#include "global.h"
#include "tile.h"

void generate(SDL_Renderer *render, Tile* tile)
{
	int x = 0;
	int y = 0;
	int row = 0;
	int col = 0;
	SDL_Surface* surface = IMG_Load("./img/grass.png");
	SDL_Texture* texture_surface = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
	while (row < MAX_ROW && col < MAX_COL) {
		if (row < MAX_ROW) {
			tile->rect = {x, y, tile->w, tile->h};
			SDL_RenderCopy(render, texture_surface, NULL, &tile->rect);
			row++;
			x += tile->w;
			if (row == MAX_ROW) {
				row = 0;
				x = 0;
				col++;
				y += tile->h;
			}
		}
	}
}
