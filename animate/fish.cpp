/* Dan McCormack
	3/28/2012
	Lab 8: Deliverable
	Animating Fish
*/
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream> //added for debugging
#include <string>

#include "fish.h"

fish::fish(){
	// Initialize offsets
	x = 0;
	y = 0;

	// Initialize velocity
	xVel = 0;
	yVel = 0;
}

void fish::handle_input(SDL_Event event){
	// If key pressed
	if(event.type == SDL_KEYDOWN){
		// Adjust velocity
		switch(event.key.keysym.sym){
			case SDLK_UP: yVel -= fish_height / 2; break;
			case SDLK_DOWN: yVel += fish_height / 2; break;
			case SDLK_LEFT: xVel -= fish_width / 2; break;
			case SDLK_RIGHT: xVel += fish_width / 2; break;
		}
	}
	// If key released
	else if(event.type == SDL_KEYUP){
		// Adjust velocity

		switch(event.key.keysym.sym){
			case SDLK_UP: yVel += fish_height / 2; break;
			case SDLK_DOWN: yVel -= fish_height / 2; break;
			case SDLK_LEFT: xVel += fish_width / 2; break;
			case SDLK_RIGHT: xVel -= fish_width / 2; break;
		}
	}
}

SDL_Surface* fish::load_image(string filename){
	// Image loaded
	SDL_Surface* loadedImage = NULL;

	// Optimized image used
	SDL_Surface* optimizedImage = NULL;

	// Load image
	loadedImage = IMG_Load(filename.c_str());

	// if image loaded
	if(loadedImage != NULL){
		// create optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);
		// Free old image
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void fish::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	// temp rectangle for offsets
	SDL_Rect offset;
	// Get offsets
	offset.x = x;
	offset.y = y;

	// Blit Surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}
