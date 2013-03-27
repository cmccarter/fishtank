/* Dan McCormack
	3/28/2013
	Lab 8: Deliverable 
	Header file to have object move
*/

// Headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

using namespace std;

// define class
class fish{
	public:
		fish(); // Constructor
		void handle_input(); // takes input
		void move(); // moves fish
		void show(); // displays fish on screen
		SDL_Surface* load_image(string);
		void apply_surface(int, int, SDL_Surface*, SDL_Surface*);

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
};
