#include <SDL_rect.h>
#include <SDL_render.h>
#include "fruit.h"

//Draw fruit
void fruit(SDL_Renderer *render, Fruit* fruit)
{
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	fruit->rect = { fruit->x, fruit->y, fruit->w, fruit->h };
	fruit->_rect_ = &fruit->rect;
	SDL_RenderDrawRect(render, &fruit->rect);

}
