
enum Direction {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

class entity {

public:
	int x;
	int y;
	int w;
	int h;
	bool alive;
	float health;
	double speed;
	Direction direction;

public:
	entity(float health,int x, int y, int w, int h, double speed) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->health = health;
		this->speed = speed;
		this->alive = true;
		this->direction = DOWN;
	}

};

void tick();
