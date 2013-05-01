#ifndef FISH_H
#define FISH_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>
#include "food.h"

using namespace std;

// define class
class fish{
	public:
		fish(); // Constructor
		fish(int, int, SDL_Surface*); // non default constructor 
		void handle_input(SDL_Event); // takes input
		void move(vector<food*>); // moves fish
		SDL_Surface* show(); // displays fish on screen
		bool iWasClicked(SDL_Event); // returns true if click was on fish

		int getX();
		int getY();
		int getXvel();
		int getYvel();
		void setYvel(double);
		void setXvel(double);
//		SDL_Rect fishBox;
		void set_clips();

		//behavior control
                void setTargets(vector<food*>);
        SDL_Rect gurgleClip[40];

		//killing commands
		void execute(); //this command terminates the fish
		int condemned(); //returns a 1 if it needs to be killed
		void setAvgHeight(int);
	private:
               //behavior controls
                int pChangeDirectionY;
		int pChangeDirectionX;
                int maxChangeDirectionY;
		int maxChangeDirectionX;
		int maxSpeed;
		double wanderTotalSpeed;
		int avgHeight;
		int turnStatus;

                //where the fish is swimming towards, -1 means it is just wandering
                int targetX;
                int targetY;

		// fish sizes
		int fish_height;
		int fish_width;
		// X and Y offsets of fish
		int x;
		int y;
		// Velocity of fish
		double xVel;
		double yVel;
		int offset;
		
		int frame;
		int status;
	
		int kill;
		//pointer to the image
		SDL_Surface* image;
};

#endif
