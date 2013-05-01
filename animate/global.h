#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>

using namespace std;

//function prototyping
	bool initialize();
	void clean_up();
	SDL_Surface* load_image(string);
	void apply_surface(int, int, SDL_Surface*, SDL_Surface*);
	void apply_rect(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);

	bool check_collision( SDL_Rect, SDL_Rect);

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
	// Rect for sprite sheeet clips
	
#endif 
