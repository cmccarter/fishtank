fishtank: animate.o fish.o timer.o food.o bubble.o
	g++ fish.o animate.o timer.o food.o bubble.o -o fishtank -lSDL -lSDL_image
animate.o: animate.cpp 
	g++ -c animate.cpp
fish.o: fish.h fish.cpp
	g++ -c fish.cpp
timer.o: timer.h timer.cpp
	g++ -c timer.cpp
food.o: food.h food.cpp
	g++ -c food.cpp
bubble.o: bubble.h bubble.cpp
	g++ -c bubble.cpp

clean: 
	rm -f *.o fishtank
