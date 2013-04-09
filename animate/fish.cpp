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
#include "food.h"

fish::fish(){
	// Initialize offsets
	x = 0;
	y = 0;

	// Initialize velocity
	xVel = 0;
	yVel = 0;

	//default fish will be a 40x40 square
	fish_height = 480;
	fish_width = 640;

	// offsets for hit box
	fishBox.y = 0;
	fishBox.x = 0;

	// Hit box dimensions
	fishBox.w = fish_width;
	fishBox.h = fish_height;
}

fish::fish(int a, int b, SDL_Surface* input){
	x = a;
	y = b;

	xVel = 0;
	yVel = 0;

	fish_height = 480;
	fish_width = 640;

	image = input;

	// offsets for hit box
	fishBox.y = 0;
	fishBox.x = 0;

	// Hit box dimensions
	fishBox.w = fish_width;
	fishBox.h = fish_height;
}

SDL_Surface* fish::show(){
        return image;
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



void fish::move(){
	//increment speed
	x+=xVel;
	y+=yVel;
	fishBox.x = x;
	fishBox.y = y;

	if((x< 0) || (x + fish_width > 1000)) xVel = -xVel;
	if((y < 0) || (y + fish_height > 600)) yVel = -yVel;
}

bool fish::iWasClicked(SDL_Event event){
	if ((event.button.x >= x)&&( event.button.x <= x + fish_width )&&(event.button.y >= y)&&( event.button.y <= y + fish_height)) return (true);
	else return (false);
}

int fish::getX(){
	return x;
}

int fish::getY(){
	return y;
}

void fish::setXvel(int xin){
	xVel = xin;
	return;
}

void fish::setYvel(int yin){
	yVel = yin;
	return;
}