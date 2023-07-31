struct Fruit {
public:
	int x;
	int y;
	int w;
	int h;
	SDL_Rect rect;
	SDL_Rect *_rect_;

};

extern void fruit(SDL_Renderer *render,Fruit* fruit);