#include <SDL_rect.h>
#include "sdlplugin.h"
SDL_Rect* _cdecl SDL_CreateRect(int x, int y, int w, int h)
{
	SDL_Rect  *rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return rect;
}
