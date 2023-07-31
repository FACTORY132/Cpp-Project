#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "global.h"
#include "sdlplugin.h"
#include "random.h"
#include "fruit.h"
#include "tile.h"
#include "snake.h"

using namespace std;

Snake sk = { next_int(SNAKE_SPAWN_MIN_X, SNAKE_SPAWN_MAX_X), next_int(SNAKE_SPAWN_MIN_Y, SNAKE_SPAWN_MAX_Y) , 2, false, RIGHT, 0 };


Fruit ft = {next_int(FRUIT_SPAWN_MIN_X, FRUIT_SPAWN_MAX_X), next_int(FRUIT_SPAWN_MIN_Y, FRUIT_SPAWN_MAX_Y), 16, 16};
Tile tile = {64, 64};



void draw(SDL_Window *window, SDL_Renderer* render)  {
	
	generate(render, &tile);
	fruit(render, &ft);
	snake(render, &sk);
	
	
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
}


void events(SDL_Window *window,SDL_Renderer* render) {

	bool quit = false;
	SDL_Event events;
	while (!quit) {
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT)
				quit = true;
			key_event(events, &sk, &ft);	
		}

		Direction* dc = &sk.direction;
		SDL_RenderClear(render);

		draw(window, render);
		move(&sk, *dc);
		eat(&sk, &ft);

		SDL_RenderPresent(render);
	}
}

int win64(const char* title,const int width, const int height)  {
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOWEVENT);

	
	if (!window) {
		SDL_Log("Failed to create SDL window: %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	
	if (!render) {
		SDL_Log("Falied to create SDL Renderer: %s", SDL_GetError());

		SDL_Quit();
		return EXIT_FAILURE;
	}
	for (int m = 0; m < sk.body_part; m++) {
		if (!&sk.body_rect[m]) {
			SDL_Log("Failed: Body Rect%s", SDL_GetError());
			SDL_Quit();
			return EXIT_FAILURE;
		}
	}
	if(!&sk.rect) {
		SDL_Log("Failed: Head Rect%s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	events(window ,render);


	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}



int main(int argc, char* args[]) {

	win64("Snake 1.0", SCREEN_W, SCREEN_H);

	return 0;
}