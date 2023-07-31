#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_keyboard.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <iostream>
#include "global.h"
#include "texture.h"
#include "random.h"
#include "fruit.h"
#include "snake.h"



//Random new direction after reset
Direction random_direction(){
	int j = next_int(1, 4);
	switch (j) {
	case 1:
		return UP;
	case 2:
		return DOWN;
	case 3:
		return RIGHT;
	case 4:
		return LEFT;
	default:
		return NONE;
	}
	
}


void eat(Snake* snake, Fruit* fruit) {
	if(SDL_HasIntersection(&snake->rect, fruit->_rect_)) {
		fruit->x = next_int(FRUIT_SPAWN_MIN_X, FRUIT_SPAWN_MAX_X);
		fruit->y = next_int(FRUIT_SPAWN_MIN_Y, FRUIT_SPAWN_MAX_Y);
		snake->body_part += PART;
	}
	
}
//Stop when intersection with screen board
void die(Snake* snake) {
	if (snake->x >= SCREEN_W_POSITIVE_BOARD || snake->x <= SCREEN_W_NEGATIVE_BOARD || snake->y >= SCREEN_H_BOARD || snake->y <= SCREEN_W_NEGATIVE_BOARD)
		snake->stop = true;
}

//Reset after die(Not auto)
void reset(Snake* snake, Fruit *fruit) {
	snake->x = next_int(SNAKE_SPAWN_MIN_X, SNAKE_SPAWN_MAX_X);
	snake->y = next_int(SNAKE_SPAWN_MIN_Y, SNAKE_SPAWN_MAX_Y);
	fruit->x = next_int(FRUIT_SPAWN_MIN_X, FRUIT_SPAWN_MAX_X);
	fruit->y = next_int(FRUIT_SPAWN_MIN_Y, FRUIT_SPAWN_MAX_Y);
	snake->direction = random_direction();
	snake->body_part = 0;
	snake->stop = false;
}


void move(Snake *snake,Direction direction)  {
	int m = (snake->stop ? 0 : static_cast<int>(snake->speed));
	switch (direction) {
	case UP:
		snake->y -= m;
		break;
	case DOWN:
		snake->y += m;
		break;
	case LEFT:
		snake->x -= m;
		break;
	case RIGHT:
		snake->x += m;
		break;
	
	}
}


void key_event(SDL_Event sdl_event, Snake* snake, Fruit* fruit) {

	if (sdl_event.type == SDL_KEYDOWN) {
		switch (sdl_event.key.keysym.sym) {
		case SDLK_DOWN:
			if(snake->direction != UP)
				snake->direction = DOWN;
			break;
		case SDLK_UP:
			if(snake->direction != DOWN)
				snake->direction = UP;
			break;
		case SDLK_LEFT:
			if(snake->direction != RIGHT)
				snake->direction = LEFT;
			break;
		case SDLK_RIGHT:
			if(snake->direction != LEFT)
				snake->direction = RIGHT;
			break;
		case SDLK_r:
			reset(snake, fruit);
			break;
		
		}
	}
	
}

//Keep body follow snake head
void moveBody(Snake* snake) {
	for (int j = snake->body_part - 1; j > 0; j--) {
		snake->body_rect[j].x = snake->body_rect[j - 1].x;
		snake->body_rect[j].y = snake->body_rect[j - 1].y;
	}
	if (snake->body_part > 0) {
		snake->body_rect[0].x = snake->x;
		snake->body_rect[0].y = snake->y;
	}
}

//For snake texture with direction
void snakeC(SDL_Renderer* render, Snake* snake, SDL_Rect* rect) {
	//Path name is in texture fill
	switch (snake->direction) {
	case UP:
		Texture::getTexture(render, rect, "snake_up");
		break;
	case DOWN:
		Texture::getTexture(render, rect, "snake_down");
		break;
	case LEFT:
		Texture::getTexture(render, rect, "snake_left");
		break;
	case RIGHT:
		Texture::getTexture(render, rect, "snake_right");
		break;
	}
}


void snake(SDL_Renderer* render, Snake* snake) {
	snake->rect = {snake->x, snake->y, SNAKE_SIZE, SNAKE_SIZE};
	snakeC(render, snake, &snake->rect);
	moveBody(snake);
	for (int i = 0; i < MAX_SIZE; i++) {
		snake->body_rect[i].w = SNAKE_SIZE;
		snake->body_rect[i].h = SNAKE_SIZE;
	}
	for (int j = 0; j < snake->body_part; j += PART) {
		if (j == 0)
			snakeC(render, snake, &snake->body_rect[j]);
		else //Path name is in texture file
			Texture::getTexture(render, &snake->body_rect[j], "snake_body");
		if (SDL_HasIntersection(&snake->rect, &snake->body_rect[j+PART*2]))
			snake->stop = true;	
	}
	die(snake);
}