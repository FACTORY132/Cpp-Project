#include <SDL_render.h>
#include <SDL_image.h>

class Texture {
public:
	static SDL_Texture* getTexture(SDL_Renderer* renderer, SDL_Rect* rect ,std::string file) {
		std::string path = "./img/" + file + ".png";
		SDL_Surface* surface = IMG_Load(path.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		SDL_RenderCopy(renderer, texture, NULL, rect);
		return texture;
	}
};