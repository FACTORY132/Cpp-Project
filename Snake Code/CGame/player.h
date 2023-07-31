#include "entity.h"

class  Player : public entity {
public:
	Player(float health, int x, int y, int w, int h, double speed) : entity(health, x ,y, w, h, speed) {
	
	}

	void move(Direction direction){
		this->direction = direction;
		switch (direction) {
		case UP:
			this->y -= static_cast<int>(speed);
			break;
		case DOWN:
			this->y += static_cast<int>(speed);
			break;
		case LEFT:
			this->x -= static_cast<int>(speed);
			break;
		case RIGHT:
			this->x += static_cast<int>(speed);
			break;
		}
	}
};

