#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream> //added for debugging
#include <string>

using namespace std;

	// Screen attributes
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP = 32;

	// Surfaces
	SDL_Surface *fish = NULL;
	SDL_Surface *screen = NULL;


bool init(){
	// Initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}

	// Setup Screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	// If error
	if(screen == NULL) return false;

	// Set Caption
	SDL_WM_SetCaption("Fish Tank", NULL);

	// if everything okay
	return true;
}

/*bool load_files(){
	// Load image
	image = Load_image("fish.png");

	// if error
	if(image == NULL){
		return false;
	}

	return true;
}*/
void clean_up(){
	// Free image
	SDL_FreeSurface(fish);
	//Quit SDL
	SDL_Quit();
}