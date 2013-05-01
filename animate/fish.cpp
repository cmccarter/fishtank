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
#include <time.h>

//creates a vector to store all food items being shown at once
vector< food* > FOOD;

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
	turnStatus = 0;
	set_clips();
}

fish::fish(int a, int b, SDL_Surface* input, int fh, int fw){
	x = a;
	y = b;

	xVel = 3;
	yVel = 3;
	offset = 0;

	frame = 0;
	fish_height = fh;
	fish_width = fw;

	image = input;
	//srand (time(NULL));

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
	maxSpeed = 8;
	wanderTotalSpeed = 9;
	avgHeight = 100 + rand()%220;
	turnStatus = 0;
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
			cout << "before..." << endl;
			SDL_BlitSurface(image, &gurgleClip[frame], screen, &offset);
			cout << "after..." << endl;
		}
		if(xVel < 0){
			SDL_BlitSurface(image, &gurgleClip[frame+20], screen, &offset);
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



void fish::move(vector< food*> FOOD){
       //look at the propensity to change direction and if we have a target
        double totalVel = sqrt(pow(xVel,2)+pow(yVel,2));
        cout << "Total Velocity: " << totalVel << endl << endl;
if (turnStatus == 0){
        if(targetX == -1 && targetY == -1) {
                //wander
		cout << "Wandering..." << endl;
                pChangeDirectionX = pChangeDirectionX + 1 + rand()%20;
                if(x<20 && xVel < 0) pChangeDirectionX = pChangeDirectionX + fabs(xVel)*pow((20-x),2);
                if(x+fish_width > 980 && xVel > 0) pChangeDirectionX = pChangeDirectionX + fabs(xVel)*pow((980-x),2);

		xVel = xVel + ((1-rand()%3) / 1);
		if (xVel > maxSpeed) xVel = xVel - (rand()%3)/1;
		if (xVel < 2 && xVel >= 0) xVel = xVel + (rand()%3)/1;
		if (xVel < -maxSpeed) xVel = xVel + (rand()%3)/1;
		if (xVel > -2 && xVel <= 0) xVel = xVel - (rand()%3)/1;

		if (y > avgHeight + 20 || y < avgHeight - 20){
			cout << "Out of average bounds." << endl;
			if(xVel == 0) xVel = 3 - rand()%7;
			yVel = -2;
			pChangeDirectionY = 0;
			//force a change of direction if the fish is moving away from its average height
			if (((y > avgHeight + 20)&&(yVel > 0))||((y < avgHeight - 20)&&(yVel < 0 ))){
				pChangeDirectionY = 5000;
			}
			//but change the direction if the fish is headed the wrong way
		}	

		pChangeDirectionY = pChangeDirectionY + rand()%2;
/*		if(y<50 && yVel < 0) pChangeDirectionY = pChangeDirectionY + fabs(yVel)*pow((50-y),2);
		if(y>550 && yVel > 0) pChangeDirectionY = pChangeDirectionY + fabs(yVel)*pow((550-y),2);
*/
        } else {
                //follow the food
		cout << "Found food..." << endl;
                if (targetX-x <= 0) xVel = 1;
         		if (sqrt(pow(targetX-x, 2) + pow(targetY - y, 2)) < 2){
         			xVel = 4;
         			yVel = 4;
     			}	
     			else xVel = (targetX - x) / 12;
		//else xVel = (targetX-x)/fabs(targetX-x)*sqrt(pow(totalVel,2)*(pow((targetX - x),2)/(pow((targetX - x),2)+pow((targetY - y),2))));
                if (targetY-y == 0) yVel = 1;
		//else yVel = (targetY-y)/fabs(targetY-y)*sqrt(pow(totalVel,2)*(pow((targetY - y),2)/(pow((targetX - x),2)+pow((targetY - y),2))));
                else yVel = (targetY - y) / 12;
		cout << "Following food! XVel, YVel : " << xVel << ", "<< yVel << endl;
        }


	if (pChangeDirectionX > maxChangeDirectionX){
				cout << "Flipped" << endl;
                xVel = -xVel;
                pChangeDirectionX = 0;
		turnStatus = 1;
        }
	if (pChangeDirectionY > maxChangeDirectionY){
                yVel = -yVel;
                pChangeDirectionY = 0;
		turnStatus = 0;
        }

//collision with food detection
        cout << "food size " << FOOD.size() << endl;
        for(int i = 0; i < FOOD.size(); i++){
                int fox = FOOD[i]->getX();
                int foy = FOOD[i]->getY();
                        int fix = getX();
                        int fiy = getY() + 50;
                if(xVel >=0)
                        {fix += 75;
                        if(((fix +25 >= fox) && (fix -25 <= fox)) && ((fiy +10 >= foy)&&(fiy -10 <= foy)))
				{FOOD[i]->execute();
                                }
                        }
                else
                    	{if(((fix +25 >= fox) && (fix -25 <= fox)) && ((fiy +10>= foy)&&(fiy -10 <= foy)))
                                {FOOD[i]->execute();
                                }
                        }
        }




	//increment speed

	 x+=xVel;
	 y+=yVel;
//	fishBox.x = x;
//	fishBox.y = y;

        if((x< 0) || (x + fish_width > 1000)){
        		cout << "Edge" << endl;
                xVel = -xVel;
                pChangeDirectionX = 0;
        }
	if((y < 0) || (y + fish_height > 600)){
                yVel = -yVel;
                pChangeDirectionY = 0;
        }
}else{
	turnStatus = turnStatus + 1;
	//7 is the pixel amount
	if (turnStatus == 7){
		turnStatus = 0;
	}
}

}

bool fish::iWasClicked(SDL_Event event){
	if ((event.button.x >= x)&&( event.button.x <= x + fish_width )&&(event.button.y >= y)&&( event.button.y <= y + fish_height)) return (true);
	else return (false);
}

int fish::getX(){
	return x - 20;
}

int fish::getY(){
	return y - 70;
}

void fish::setXvel(double xin){
	xVel = xin;
	return;
}

void fish::setYvel(double yin){
	yVel = yin;
	return;
}


void fish::set_clips(){

	for(int i = 0; i < 20; i++){
		gurgleClip[i].x = 0;
		gurgleClip[i].y = fish_height*i;
		gurgleClip[i].w = fish_width;
		gurgleClip[i].h = fish_height;
	}

	for(int j = 20; j < 40; j++){
		gurgleClip[j].x = fish_width;
		gurgleClip[j].y = fish_height*(j-20);
		gurgleClip[j].w = fish_width;
		gurgleClip[j].h = fish_height;
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
        int proximityAwareness = 50000;
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
                        targetX = FOOD[closestElement]->getX()-45;
                        targetY = FOOD[closestElement]->getY()+40;
                }
        }

	cout << "Target X: " << targetX << endl;
	cout << "Target Y: " << targetY << endl;

	return;
}

int fish::getXvel(){
	return xVel;
}

int fish::getYvel(){
	return yVel;
}

void fish::setAvgHeight(int i){
	avgHeight = i;
	return;
}
