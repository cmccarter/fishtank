fishtank: animate.o fish.o
	g++ fish.o animate.o -o fishtank -lSDL -lSDL_image
animate.o: animate.cpp 
	g++ -c animate.cpp
fish.o: fish.h fish.cpp
	g++ -c fish.cpp

clean: 
	rm -f *.o fishtank
