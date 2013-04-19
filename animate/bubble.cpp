#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "bubble.h"
#include <string>
#include <stdlib.h>

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
	int kill = 0;
}

bubble::bubble(SDL_Event event, SDL_Surface* bubblepic){
	x = event.button.x;
	y = event.button.y;
	
	xStart = x;

	xVel = 2;
	yVel = 10;

	int kill = 0;

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

void bubble::execute(){
	kill = 1;
}

int bubble::getX(){
	return x;
}

int bubble::getY(){
	return y;
}

int bubble::condemned(){
	return kill;
}
