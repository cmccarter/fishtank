


SDL_Surface* fish::load_image(string filename){
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

void fish::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	// temp rectangle for offsets
	SDL_Rect offset;
	// Get offsets
	offset.x = x;
	offset.y = y;

	// Blit Surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}

bool init(){
	// Initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}

	// Setup Screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	// If error
	if(screen == NULL) return false;

	// Set Caption
	SDL_WM_SetCaption("Event Driven Motion", NULL);

	// if everything okay
	return true;
}

/*bool load_files(){
	// Load image
	image = Load_image("fish.png");

	// if error
	if(image == NULL){
		return false;
	}

	return true;
}*/
void clean_up(){
	// Free image
	SDL_FreeSurface(fish);
	//Quit SDL
	SDL_Quit();
}