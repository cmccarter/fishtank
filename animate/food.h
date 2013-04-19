#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

using namespace std;

// define class
class food{
	private:
		//x and y offsets
		int x;
		int y;

		//velocity of food
		int xVel;
		int yVel;

		//order to delete this object
		int kill;
		SDL_Surface* image;
	
	public:
		food();
		food(SDL_Event, SDL_Surface*);
		void move();
		SDL_Surface* show();

		int getX();
		int getY();

		SDL_Rect foodBox;

		//kill functions
		void execute();
		int condemned();
};
