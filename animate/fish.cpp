/* Dan McCormack and Conor McCarter
	3/28/2012
	Lab 8: Deliverable
	Animating Fish
*/

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream> //added for debugging
#include <string>
#include <math.h>

#include "fish.h"
#include "food.h"
#include "global.h"


fish::fish(){
	// Initialize offsets
	x = 0;
	y = 0;

	// Initialize velocity
	xVel = 0;
	yVel = 0;

	offset = 0;
	//default fish will be a 40x40 square
	fish_height = 200;
	fish_width = 100;

	// offsets for hit box
//	fishBox.y = 0;
//	fishBox.x = 0;

	// Hit box dimensions
//	fishBox.w = fish_width;
//	fishBox.h = fish_height;

	//killing variable
	kill = 0;

	//behavior control
        pChangeDirectionX = 0;
	pChangeDirectionY = 0;
        maxChangeDirectionX = 500;
	maxChangeDirectionY = 20;
	maxSpeed = 15;
	wanderTotalSpeed = 9;
	avgHeight = 200;
	set_clips();
}

fish::fish(int a, int b, SDL_Surface* input){
	x = a;
	y = b;

	xVel = 3;
	yVel = 3;
	offset = 0;

	frame = 0;
	fish_height = 200;
	fish_width = 100;

	image = input;

	// offsets for hit box
//	fishBox.y = 0;
//	fishBox.x = 0;

	// Hit box dimensions
//	fishBox.w = fish_width;
//	fishBox.h = fish_height;

	//killing variable
	kill = 0;

	//behavior control
        pChangeDirectionX = 0;
	pChangeDirectionY = 0;
        maxChangeDirectionX = 500;
	maxChangeDirectionY = 20;
	maxSpeed = 15;
	wanderTotalSpeed = 9;
	avgHeight = 200;
	set_clips();
}

SDL_Surface* fish::show(){
		frame++;
		if(frame >= 20){
				frame = 0;
		}
		SDL_Rect offset;
		offset.x = getX();
		offset.y = getY();
		if(xVel >= 0){
			SDL_BlitSurface(fishtest, &gurgleClip[frame], screen, &offset);
		}
		if(xVel < 0){
			SDL_BlitSurface(fishtest, &gurgleClip[frame+20], screen, &offset);
		}


}

void fish::handle_input(SDL_Event event){
	// If key pressed
	if(event.type == SDL_KEYDOWN){
		// Adjust velocity
		switch(event.key.keysym.sym){
			case SDLK_UP: yVel -= fish_height / 15; break;
			case SDLK_DOWN: yVel += fish_height/ 15; break;
			case SDLK_LEFT: xVel -= fish_width/ 15; break;
			case SDLK_RIGHT: xVel += fish_width/ 15; break;
		}
	}
	// If key released
	else if(event.type == SDL_KEYUP){
		// Adjust velocity

		switch(event.key.keysym.sym){
			case SDLK_UP: yVel += fish_height/ 15; break;
			case SDLK_DOWN: yVel -= fish_height/ 15; break;
			case SDLK_LEFT: xVel += fish_width/ 15; break;
			case SDLK_RIGHT: xVel -= fish_width/ 15; break;
		}
	}

}



void fish::move(){
       //look at the propensity to change direction and if we have a target
        double totalVel = sqrt(pow(xVel,2)+pow(yVel,2));
        if(targetX == -1 && targetY == -1) {
                //wander
		cout << "Wandering..." << endl;
                pChangeDirectionX = pChangeDirectionX + 1;
                if(x<20 & xVel < 0) pChangeDirectionX = pChangeDirectionX + fabs(xVel)*pow((20-x),2);
                if(x+fish_width > 980 & xVel > 0) pChangeDirectionX = pChangeDirectionX + fabs(xVel)*pow((980-x),2);
		

		if (y > avgHeight + 20 || y < avgHeight - 20){
			pChangeDirectionY = 0;
			//force a change of direction if the fish is moving away from its average height
			if (((y > avgHeight + 20)&&(yVel > 0))||((y < avgHeight - 20)&&(yVel < 0 ))){
				pChangeDirectionY = 5000;
			}
			//but change the direction if the fish is headed the wrong way
		}	

		pChangeDirectionY = pChangeDirectionY + 1;
		if(y<50 & yVel < 0) pChangeDirectionY = pChangeDirectionY + fabs(yVel)*pow((50-y),2);
		if(y>550 & yVel > 0) pChangeDirectionY = pChangeDirectionY + fabs(yVel)*pow((550-y),2);

        } else {
                //follow the food
		cout << "Found food..." << endl;
                xVel = (targetX-x)/fabs(targetX-x)*sqrt(pow(totalVel,2)*(pow((targetX - x),2)/(pow((targetX - x),2)+pow((targetY - y),2))));
                yVel = (targetY-y)/fabs(targetY-y)*sqrt(pow(totalVel,2)*(pow((targetY - y),2)/(pow((targetX - x),2)+pow((targetY - y),2))));
		cout << "Following food! XVel, YVel : " << xVel << ", "<< yVel << endl;
        }


	if (pChangeDirectionX > maxChangeDirectionX){
                xVel = -xVel;
                pChangeDirectionX = 0;
        }
	if (pChangeDirectionY > maxChangeDirectionY){
                yVel = -yVel;
                pChangeDirectionY = 0;
        }




	//increment speed
	x+=xVel;
	y+=yVel;
//	fishBox.x = x;
//	fishBox.y = y;

        if((x< 0) || (x + fish_width > 1000)){
                xVel = -xVel;
                pChangeDirectionX = 0;
        }
	if((y < 0) || (y + fish_height > 600)){
                yVel = -yVel;
                pChangeDirectionY = 0;
        }

}

bool fish::iWasClicked(SDL_Event event){
	if ((event.button.x >= x)&&( event.button.x <= x + fish_width )&&(event.button.y >= y)&&( event.button.y <= y + fish_height)) return (true);
	else return (false);
}

int fish::getX(){
	return x;
}

int fish::getY(){
	return y;
}

void fish::setXvel(int xin){
	xVel = xin;
	return;
}

void fish::setYvel(int yin){
	yVel = yin;
	return;
}


void fish::set_clips(){

	for(int i = 0; i < 20; i++){
		gurgleClip[i].x = 0;
		gurgleClip[i].y = 80*i;
		gurgleClip[i].w = 107;
		gurgleClip[i].h = 80;
	}

	for(int j = 20; j < 40; j++){
		gurgleClip[j].x = 107;
		gurgleClip[j].y = 80*(j-20);
		gurgleClip[j].w = 107;
		gurgleClip[j].h = 80;
	}
}


void fish::execute(){
        kill = 1;
}

int fish::condemned(){
        return (kill);
}

void fish::setTargets(vector< food*> FOOD){
	
	cout << "Setting targets..." << endl;
        //as of now, this block only looks for food
        int closestDistance;
        int closestElement;
        //how far the fish should be able to sense food (x^2 + y^2)
        int proximityAwareness = 500000;
        int tempDistance = 0;

        //find closest food
        if (FOOD.size() == 0){
                targetX = -1;
                targetY = -1;
        } else {
                //just the farthest away possible
                closestDistance = 2000000;
                closestElement = -1;
                for(int i = 0; i < FOOD.size(); i++){
                        tempDistance = ((x - FOOD[i]->getX())*(x - FOOD[i]->getX())) + ((y - FOOD[i]->getY())*(y - FOOD[i]->getY()));
                        if( tempDistance < closestDistance && tempDistance < proximityAwareness){
                                closestElement = i;
                                closestDistance = tempDistance;
                        }
                }
		cout << "Closest Element: " << closestElement << endl;
		cout << "Closest Distance: " << closestDistance <<  endl;
                if(closestElement == -1){
                        targetX = -1;
                        targetY = -1;
                } else {
                        targetX = FOOD[closestElement]->getX();
                        targetY = FOOD[closestElement]->getY();
                }
        }

	cout << "Target X: " << targetX << endl;
	cout << "Target Y: " << targetY << endl;

	return;
}

