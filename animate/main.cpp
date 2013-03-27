//this is the main function for our fishtank. 
//this will call on all initializer functions.
//Conor McCarter
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>

using namespace std;

int main(void){



//try initializing screen
	if (init() != 1){
		return 1;
	}

	//easy program delay
	int x;
	cin >> x;


	return 0;
}