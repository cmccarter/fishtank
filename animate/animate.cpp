#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream> //added for debugging
#include <string>
#include "fish.h"

using namespace std;

	//function prototyping
	bool initialize();
	void clean_up();

	// Screen attributes
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP = 32;

	// Surfaces
	SDL_Surface *fishimage = NULL;
	SDL_Surface *screen = NULL;


int main(void){
	//declare some variables
	SDL_Surface* background = NULL;


	//try initializing screen
	if (initialize() != 1){
		cout << "Initialization failed." << endl;
		return 1;
	}

	//initialize a fish for testing
	fish trialFish;

	//try out image storing
	//yes, I know I'm putting the background in a fish object
	background = trialFish.load_image("Background.png");
	trialFish.apply_surface(0, 0, background, screen);

	//this updates the screen
	if( SDL_Flip ( screen) == -1)
	{
		cout << "There was a problem updating the screen." << endl;
		return 1;
	}

	//easy program delay so we do not immediately exit
	int x;
	cin >> x;


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
	SDL_FreeSurface(fishimage);
	//Quit SDL
	SDL_Quit();
}
