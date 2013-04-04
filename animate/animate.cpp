#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream> //added for debugging
#include <string>
#include "timer.h"
#include "fish.h"

using namespace std;

	//function prototyping
	bool initialize();
	void clean_up();

	//screen attributes
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP = 32;

	//frames per second
	const int FRAMES_PER_SECOND = 30;

	//surfaces 
	SDL_Surface *screen = NULL;

	//prepare for possible event
	SDL_Event event;

int main(void){

/* ----------------MAJOR INITIALIZATION----------------- */

	//declare some variables
	SDL_Surface* background = NULL;

	//try initializing screen
	if (initialize() != 1){
		cout << "Initialization failed." << endl;
		return 1;
	}

	//the quit master flag
	bool quit = false;

	//keep track of the current frame
	int frame = 0;

	//we want to cap the frame rate for fast computers
	bool cap = true;

	//frame rate regulator
	Timer fps;

/* -----------------END MAJOR INITIALIZATION ------------- */
/* -----------------ELEMENT INITIALIZATION --------------- */
	//initialize a fish for testing
	fish trialFish;

	//try out image storing
	//yes, I know I'm putting the background in a fish object
	background = trialFish.load_image("Background.png");
	trialFish.apply_surface(0, 0, background, screen);

/* ----------------- END ELEMENT INITIALIZATION ----------- */
/* ----------------- MAIN LOOP ---------------------------- */

	while( quit == false ){

	//start the frame timer 
	fps.start();

	//while there are no events to handle
	while ( SDL_PollEvent( &event) )
	{
		//if a key was pressed
		if( event.type == SDL_KEYDOWN )
		{
			//if 'q' was pressed
			if(event.key.keysym.sym == SDLK_q )
			{
				//quit on next loop
				quit = true;
			}
		}

		//if the user Xed the window
		else if( event.type == SDL_QUIT )
		{
			//quit the program
			quit = true;
		}
	}

	//this updates the screen
	if( SDL_Flip (screen) == -1)
	{
		cout << "There was a problem updating the screen." << endl;
		return 1;
	}

	//increment frame counter
	frame++;

	//if we want to cap the frame rate
	if( ( cap == true ) && (fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
	{
		//sleep the remaining frame time
		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	}

	}

/* -------------------END MAIN LOOP------------------------ */
	//cleanup here if needed

	return 0;
}


bool initialize(){
	// Initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		cout << "There was a problem initializing everything."<< endl;
		return false;
	}

	// Setup Screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	// If error
	if(screen == NULL){
		cout << "There was a problem initializing the screen." << endl;
		return false;
	}

	// Set Caption
	SDL_WM_SetCaption("Fish Tank", NULL);

	// if everything okay
	return true;
}

/*
bool load_files(string filename){
	// Load image
	image = Load_image(" filename.c_str() );

	// if error
	if(image == NULL){
		return false;
	}

	return true;
}*/

void clean_up(){
	// Free image
	SDL_FreeSurface(NULL);
	//Quit SDL
	SDL_Quit();
}
