#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream> //added for debugging
#include <vector>
#include <string>
#include "timer.h"
#include "fish.h"
#include "food.h"

using namespace std;

	//function prototyping
	bool initialize();
	void clean_up();
	SDL_Surface* load_image(string);
	void apply_surface(int, int, SDL_Surface*, SDL_Surface*);


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
	
	//the mouse offsets
	int x = 0;
	int y = 0;

	//Declare images below. Loading is time and memory intensive...
	//So we will load images here, to pass to objects, not in objects themselves.

	//declare background
	cout << "Loading background image 1." << endl;
	SDL_Surface* background = load_image("Background.png");

	//declare every other surface
	cout << "Loading fishfood image." << endl;
	SDL_Surface* fishfood = load_image("small_bubble.png"); //use bubble for test
	cout << "Loading first fish." << endl;	


/* -----------------END MAJOR INITIALIZATION ------------- */
/* -----------------ELEMENT INITIALIZATION --------------- */

	//creates a vector to store all food items being shown at once
	vector< food* > FOOD;
	//creates a vector to store all the fish
	vector< fish* > FISH;

	//active fish (this variable will indicate which fish is active) (-1 means no fish)
	int active_fish = -1;

/* ----------------- END ELEMENT INITIALIZATION ----------- */
/* ----------------- MAIN LOOP ---------------------------- */

	while( quit == false ){

	//start the frame timer 
	fps.start();

/* -------------MAIN LOOP: EVENTS ------------------------- */

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
			else
			{
				//if it was not a 'q', pass to the active fish to interpret
				if(active_fish >= 0 && active_fish < FISH.size() ){
					FISH[active_fish]->handle_input(event);
				}
			}
		}
		//if the user Xed the window
		else if( event.type == SDL_QUIT )
		{
			//quit the program
			quit = true;
		}

		//if the mouse clicks
		else if( event.type == SDL_MOUSEBUTTONDOWN )
		{
			if(event.button.button == SDL_BUTTON_RIGHT )
			{
				//on right click, make new fish food
				FOOD.push_back(new food(event, fishfood));
			}
			else if (event.button.button == SDL_BUTTON_LEFT )
			{
				//fish selection
				//go through fish vector to check for a fish under the cursor
				for(int i = 0; i < FISH.size(); i++){
					//if iWasClicked indicates that a fish was clicked, make that fish the selected
					if(FISH[i]->iWasClicked(event)){
						active_fish = i;
						break;
					}
				}
			}
		}
	}

/* ---------------------MAIN LOOP: LOGIC ---------------- */
	//move functions for each object
	for(int i = 0; i < FOOD.size(); i++){
		FOOD[i]->move();
	}

	for(int j = 0; j < FISH.size(); j++){
		FISH[j]->move();
	}

/* ---------------------MAIN LOOP: RENDERING ------------ */
	//apply background
	apply_surface(0, 0, background, screen);

	//apply every other object
	for(int I = 0; I< FOOD.size(); I++){
		apply_surface(FOOD[I]->getX(),FOOD[I]->getY(),FOOD[I]->show(),screen);	
	}

	for(int J = 0; J< FISH.size(); J++){
		apply_surface(FISH[J]->getX(),FISH[J]->getY(),FISH[J]->show(),screen);
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

	//check for element killing (Conor will explain)
	
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

SDL_Surface* load_image(string filename){
	// Image loaded
	SDL_Surface* loadedImage = NULL;

	// Optimized image used
	SDL_Surface* optimizedImage = NULL;

	// Load image
	loadedImage = IMG_Load(filename.c_str());

	// if image loaded
	if(loadedImage != NULL){
		// create optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);
		// Free old image
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	
	// temp rectangle for offsets
	SDL_Rect offset;
	// Get offsets
	offset.x = x;
	offset.y = y;

	// Blit Surface
	SDL_BlitSurface(source, NULL, destination, &offset);
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
