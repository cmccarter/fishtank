#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "food.h"
#include <string>

using namespace std;

food::food(){
	//position
	x = 0;
	y = 0;
	foodBox.x = x;
	foodBox.y = y;

	//velocity
	xVel = 0;
	yVel = 1;

	//self destruct order
	int kill = 0;
	foodBox.w = 20;
	foodBox.h = 20;
}

food::food(SDL_Event event, SDL_Surface* fishfood){
	x = event.button.x;
	y = event.button.y;
	foodBox.x = x;
	foodBox.y = y;
	foodBox.w = 20;
	foodBox.h = 20;
	xVel = 0;
	yVel = 5;

	int kill = 0;

	image = fishfood;
}

void food::move(){
	x += xVel;
	y += yVel;



	//if the food has hit the bottom of the tank
	if( y > 470 ){
		//moveback
		y -= yVel;
	}
}

SDL_Surface* food::show(){
	return image;
}

void food::destruct(){
	kill = 1;
}

int food::getX(){
	return x;
}

int food::getY(){
	return y;
}
