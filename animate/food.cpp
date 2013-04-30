#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "food.h"
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

food::food(){
	//position
	x = 0;
	y = 0;
	foodBox.x = x;
	foodBox.y = y;

	//velocity
	xVel = 1;
	yVel = 1;

	//self destruct order
	kill = 0;
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
	xVel = 2;
	yVel = 5;

	xStart = event.button.x;

	if (event.button.y > 470) kill = 1;
	else kill = 0; 
	age = 0;
	maxAge = 150;

	image = fishfood;
}

void food::move(){
	y += yVel;


	//if the food has hit the bottom of the tank
	if( y > 470 ){
		//moveback
		y -= yVel;
		age = age + 1;
	}

	if (age > maxAge){
		execute();
	}

	if (y < 460){
		if(x < xStart - 5) x +=xVel;
		else if (x > xStart + 5) x -= xVel;
		else x = x + (rand()%(2*xVel + 1))-2;
	}

}

SDL_Surface* food::show(){
	return image;
}

int food::getX(){
	return x;
}

int food::getY(){
	return y;
}

void food::execute(){
        kill = 1;
}

int food::condemned(){
        return (kill);
}

