#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include "screen.h"
#include "palette.h"
#include "input.h"

#define TRUE 1
#define FALSE 0
#define MAX_FILES 20

char* paths[MAX_FILES] = { NULL };
const int FORMATS = 7;
int run = TRUE;
char filename[256];
SDL_Window* main_window;

int stringToInt(char* s) {
	int length = strlen(s);
	int result = 0;
	for(int i = 0; i < length;){
		result += (s[i] - 48) * pow(10, length - ++i);
	}
	return result;
}

int setTexturePaths() {
	const char* const supported_formats[] = {".png", ".jpg", ".jpeg", ".gif", ".bmp", ".ico", ".tga"};

	char* CWD_str = getcwd(NULL, 0);
	DIR* CWD = opendir(CWD_str);

	struct dirent* file;

	int i = 0, count = 0;

	while( (file = readdir(CWD)) ) {
		if( file->d_type == DT_REG ){
			int acceptable_format = FALSE;
			for(int i = 0; i < FORMATS; i++){

				if (strstr(file->d_name, supported_formats[i])) {
					//found a texture file
					fflush(stdout);
					acceptable_format = TRUE;
					paths[count] = (char*)malloc(strlen(CWD_str) + strlen(file->d_name) + 2);
					strcpy(paths[count], CWD_str);
					paths[count][strlen(CWD_str)] = '/';
					strcpy(paths[count] + strlen(CWD_str) + 1, file->d_name);
					printf("Found supported file: %s\n", paths[i]);
					if(++count == MAX_FILES){
						printf("You have reached the max number of supported textures: %d", MAX_FILES);
						printf("Exiting texxture loading");
						closedir(CWD);
						return MAX_FILES;
					}
					break;
				}

			}
			if(!acceptable_format){

				printf("Found unsupported file: %s\n", file->d_name);
				fflush(stdout);

			}
		} 
	}
	closedir(CWD);
	free(CWD_str);
	return count;
}

void freePaths(char** paths){
	for(int i = 0; i < MAX_FILES; i++){
		free(paths[i]);
	}
}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);

	if ( argc < 3 ) exit(69);

	int w = stringToInt(argv[1]);
	int h = stringToInt(argv[2]);

	printf("Width %d and Height %d\n", w, h);
	fflush(stdout);

	main_window = SDL_CreateWindow("Teditor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);

	if (!main_window) {
		printf("Error opening window: %s\n", SDL_GetError());
	}

	SDL_Renderer* main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_SOFTWARE);

	if (!main_renderer) {
		printf("Error creating rendering context: %s\n", SDL_GetError());
	}

	int num_textures = setTexturePaths();

	if (num_textures == 0) {
		printf("No Textures found. Aborting");
		return 255;
	}

	struct Screen screen;
	struct Palette palette;

	screenInit(&screen, main_renderer, "/home/pepe/projects/teditor/default.jpg", w, h, 100, 100);
	paletteInit(&palette, paths, num_textures);
	//initialized by setTexturePaths
	freePaths(paths);
	
	while( run == TRUE ){
		SDL_SetRenderDrawColor(main_renderer, 255, 0, 0, 255);
		SDL_SetRenderDrawColor(palette.renderer, 255, 0, 0, 255);

		processEvents(&screen, &palette);
		
		screenUpdate(&screen);
		paletteUpdate(&palette);

		SDL_RenderPresent(main_renderer);
		SDL_RenderPresent(palette.renderer);
	}
	
	screenDestroy(&screen);
	paletteDestroy(&palette);
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyRenderer(palette.renderer);
	SDL_Quit();
	return 0;
}
