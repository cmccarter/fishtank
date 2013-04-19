#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

using namespace std;

// define class
class bubble{
	private:
		//x and y offsets
		int x;
		int y;

		//starting x position
		int xStart;

		//velocity of food
		int xVel;
		int yVel;

		//order to delete this object
		int kill;
		SDL_Surface* image;
	
	public:
		bubble();
		bubble(SDL_Event, SDL_Surface*);
		void move();
		SDL_Surface* show();
		void execute();	

		int getX();
		int getY();
		int condemned();
};
