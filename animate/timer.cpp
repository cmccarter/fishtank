#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>

#include "timer.h"

using namespace std;

Timer::Timer(){
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

bool Timer::is_started(){
	return started;
}

bool Timer::is_paused(){
	return paused;
}

void Timer::start(){
	//start timer
	started = true;

	//unpause timer
	paused = false;

	//get clock time
	startTicks = SDL_GetTicks();
}

void Timer::stop(){
	//stop timer
	started = false;

	//unpause timer
	paused = false;
}

void Timer::pause(){
	//if timer is running and isn't paused
	if ( ( started == true ) && (paused == false ) )
	{
		//pause timer
		paused = true;

		//calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause(){
	//if the timer is paused
	if( paused == true )
	{	
		//unpause
		paused = false;
	
		//reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//reset the paused ticks
		pausedTicks = 0;
	}
}

int Timer::get_ticks(){
	//is timer running?
	if (started == true )
	{
		//is timer paused?
		if (paused == true )
		{
			//return number of ticks when timer was paused
			return pausedTicks;
		}
		else
		{
			//return current time minus start time
			return SDL_GetTicks() - startTicks;
		}
	}

	//if the timer isn't running
	return 0;
}
