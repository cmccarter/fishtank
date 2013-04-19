fishtank: animate.o fish.o timer.o food.o bubble.o
	g++ fish.o animate.o timer.o food.o bubble.o -o fishtank -lSDL -lSDL_image
animate.o: animate.cpp global.h 
	g++ -c animate.cpp
fish.o: fish.h fish.cpp global.h
	g++ -c fish.cpp
timer.o: timer.h timer.cpp global.h
	g++ -c timer.cpp
food.o: food.h food.cpp global.h
	g++ -c food.cpp
bubble.o: bubble.h bubble.cpp global.h
	g++ -c bubble.cpp

clean: 
	rm -f *.o fishtank
