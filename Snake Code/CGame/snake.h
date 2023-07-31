#define MAX_SIZE 200000
#define SNAKE_SIZE 24
#define PART SNAKE_SIZE / 2

enum Direction {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	NONE = 4
};

struct Snake {
 	int x;
	int y;
	double speed;
	bool stop = false;
	Direction direction;
	int body_part;
	SDL_Rect rect;
	SDL_Rect body_rect[MAX_SIZE];
};

//Main snake method
extern void snake(SDL_Renderer *renderer, Snake* snake);

//Snake intersection with fruit
extern void eat(Snake* snake, Fruit* fruit);

//Snake direction change keys
extern void key_event(SDL_Event sdl_event ,Snake* snake, Fruit* fruit);

//Snake movement with direction
extern void move(Snake *snake, Direction direction);

