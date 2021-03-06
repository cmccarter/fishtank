#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include "fish.h"

using namespace std;

//function prototyping
	bool initialize();
	void clean_up();
	SDL_Surface* load_image(string);
	void apply_surface(int, int, SDL_Surface*, SDL_Surface*);
	void apply_rect(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);
	double getDistance(fish*, fish*);
	void checkCollision(vector<fish*>);
	//screen attributes
extern 	const int SCREEN_WIDTH;
extern 	const int SCREEN_HEIGHT;
extern 	const int SCREEN_BPP;
	//frames per second
extern 	const int FRAMES_PER_SECOND;
	//surfaces 
extern 	SDL_Surface *screen;

	//prepare for possible event
extern 	SDL_Event event;

	// Rect for tank constraints
extern 	SDL_Rect tank;
extern 	SDL_Surface* fishtest;
extern SDL_Surface* silverfish;
extern SDL_Surface* goldfish;
	// Rect for sprite sheeet clips
	
#endif 
