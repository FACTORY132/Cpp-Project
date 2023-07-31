#define MAX_ROW SCREEN_W / 60
#define MAX_COL SCREEN_H / 60

struct Tile {
	int w;
	int h;
	SDL_Rect rect;
};

void generate(SDL_Renderer *render, Tile *tile);