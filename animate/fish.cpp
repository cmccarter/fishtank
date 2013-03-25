/* Dan McCormack
	3/28/2012
	Lab 8: Deliverable
	Animating Fish
*/
	// Screen attributes
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;

	// Surfaces
	SDL_Surface *fish = NULL;
	SDL_Surface *screen = NULL;


fish::fish(){
	// Initialize offsets
	x = 0;
	y = 0;

	// Initialize velocity
	xVel = 0;
	yVel = 0;
}



void fish::handle_input(){
	// If key pressed
	if(event.type == SDL_KEYDOWN){
		// Adjust velocity
		switch(event.key.keysym.sym){
			case SDLK_UP: yVel -= FISH_HEIGHT / 2; break;
			case SDLK_DOWN: yVel += FISH_HEIGHT / 2; break;
			case SDLK_LEFT: xVel -= FISH_WIDTH / 2; break;
			case SDLK_RIGHT: xVel += FISH_WIDTH / 2; break;
		}
	}
	// If key released
	else if(event.type == SDL_KEYUP){
		// Adjust velocity

		switch(event.key.keysym.sym){
			case SDLK_UP: yVel += FISH_HEIGHT / 2; break;
			case SDLK_DOWN: yVel -= FISH_HEIGHT / 2; break;
			case SDLK_LEFT: xVel += FISH_WIDTH / 2; break;
			case SDLK_RIGHT: xVel -= FISH_WIDTH / 2; break;
		}
	}
}

