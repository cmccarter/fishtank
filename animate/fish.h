/* Dan McCormack
	3/28/2013
	Lab 8: Deliverable 
	Header file to have object move
*/

// Headers

#ifndef FISH_H
#define FISH_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

using namespace std;

// define class
class fish{
	public:
		fish(); // Constructor
		fish(int, int, SDL_Surface*); // non default constructor 
		void handle_input(SDL_Event); // takes input
		void move(); // moves fish
		SDL_Surface* show(); // displays fish on screen
		bool iWasClicked(SDL_Event); // returns true if click was on fish

		int getX();
		int getY();
		void setYvel(int);
		void setXvel(int);
		SDL_Rect fishBox;
		void set_clips();

	private:
		// fish sizes
		int fish_height;
		int fish_width;
		// X and Y offsets of fish
		int x;
		int y;
		// Velocity of fish
		int xVel;
		int yVel;
		int offset;
		
		int frame;
		int status;
	

	
		//pointer to the image
		SDL_Surface* image;
};

#endif