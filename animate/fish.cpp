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
#include "global.h"


extern SDL_Rect gurgleClip[3];
fish::fish(){
	// Initialize offsets
	x = 0;
	y = 0;

	// Initialize velocity
	xVel = 0;
	yVel = 0;

	offset = 0;
	//default fish will be a 40x40 square
	fish_height = 200;
	fish_width = 100;

	// offsets for hit box
	fishBox.y = 0;
	fishBox.x = 0;

	// Hit box dimensions
	fishBox.w = fish_width;
	fishBox.h = fish_height;

	//killing variable
	kill = 0;
}

fish::fish(int a, int b, SDL_Surface* input){
	x = a;
	y = b;

	xVel = 0;
	yVel = 0;
	offset = 0;

	frame = 0;
	fish_height = 200;
	fish_width = 100;

	image = input;

	// offsets for hit box
	fishBox.y = 0;
	fishBox.x = 0;

	// Hit box dimensions
	fishBox.w = fish_width;
	fishBox.h = fish_height;

	//killing variable
	kill = 0;
}

SDL_Surface* fish::show(){
		frame++;
		if(frame >= 3){
				frame = 0;
		}
		apply_rect(SCREEN_WIDTH - fish_width, SCREEN_HEIGHT - fish_height, fishtest, screen, &gurgleClip[frame]);
       return image;
}

void fish::handle_input(SDL_Event event){
	// If key pressed
	if(event.type == SDL_KEYDOWN){
		// Adjust velocity
		switch(event.key.keysym.sym){
			case SDLK_UP: yVel -= fish_height / 15; break;
			case SDLK_DOWN: yVel += fish_height/ 15; break;
			case SDLK_LEFT: xVel -= fish_width/ 15; break;
			case SDLK_RIGHT: xVel += fish_width/ 15; break;
		}
	}
	// If key released
	else if(event.type == SDL_KEYUP){
		// Adjust velocity

		switch(event.key.keysym.sym){
			case SDLK_UP: yVel += fish_height/ 15; break;
			case SDLK_DOWN: yVel -= fish_height/ 15; break;
			case SDLK_LEFT: xVel += fish_width/ 15; break;
			case SDLK_RIGHT: xVel -= fish_width/ 15; break;
		}
	}

}



void fish::move(){
	//increment speed
	x+=xVel;
	y+=yVel;
	fishBox.x = x;
	fishBox.y = y;

	if((x< 0) || (x + 2*fish_width > 1000)) xVel = -xVel;
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

void fish::set_clips(){

	gurgleClip[0].x = 0;
	gurgleClip[0].y = 0;
	gurgleClip[0].w = 640;
	gurgleClip[0].h = 480;

	gurgleClip[1].x = 0;
	gurgleClip[1].y = 480;
	gurgleClip[1].w = 640;
	gurgleClip[1].h = 480;

	gurgleClip[2].x = 0;
	gurgleClip[2].y = 480*2;
	gurgleClip[2].w = 640;
	gurgleClip[2].h = 480;
}

void fish::execute(){
        kill = 1;
}

int fish::condemned(){
        return (kill);
}

