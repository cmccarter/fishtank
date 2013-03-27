//this is the main function for our fishtank. 
//this will call on all initializer functions.
//Conor McCarter
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

using namespace std;

int main(void){

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return 1;    
	}


}