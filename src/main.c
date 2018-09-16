#include <string.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/level.h"

int stringToInt(char* s) {
	int length = strlen(s);
	int result = 0;
	for(int i = 0; i < length;){
		result += (s[i] - 48) * pow(10, length - ++i);
	}
	return result;
}

int main(int argc, char** argv) {
	if ( argc < 3 ) {
		exit(69);
	}
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);
	int w = stringToInt(argv[1]);
	int h = stringToInt(argv[2]);
	printf("Width %d and Height %d", w, h);
	fflush(stdout);
	SDL_Window* window = SDL_CreateWindow("Teditor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	if (!window) {
		printf("Error opening window: %s", SDL_GetError());
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer) {
		printf("Error creating rendering context: %s", SDL_GetError());
	}
	struct Level level;
	levelInit(&level, renderer, "/home/pepe/projects/teditor/default.jpg", w, h, 100, 100);
	while(1){
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, IMG_Load("/home/pepe/projects/teditor/default.jpg")), NULL, NULL);
		levelUpdate(&level);
		SDL_RenderPresent(renderer);
	}
	//struct Level level;	
	SDL_Quit();
}
