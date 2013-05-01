#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "bubble.h"
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

bubble::bubble(){
	//position
	x = 0;
	y = 0;

	//velocity
	xVel = 2;
	yVel = 10;

	xStart = 0;

	//self destruct order
	kill = 0;
}

bubble::bubble(SDL_Event event, SDL_Surface* bubblepic){
	x = event.button.x;
	y = event.button.y + 3 - rand()%5;
	
	xStart = x;

	xVel = 2;
	yVel = 10;

	kill = 0;

	image = bubblepic;
}

void bubble::move(){
	y -= yVel;


	if (x < xStart - 5) x += xVel;	
	else if (x > xStart + 5) x -= xVel;
	else x = x + ( rand() % ( 2*xVel + 1 ) ) - 2;	

	if (y < 0) execute();
}

SDL_Surface* bubble::show(){
	return image;
}

int bubble::getX(){
	return x;
}

int bubble::getY(){
	return y;
}

void bubble::execute(){
	kill = 1;
}

int bubble::condemned(){
	return (kill);
}
