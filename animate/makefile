fishtank: animate.o fish.o
	g++ fishtank fish.o animate.o -lSDL -lSDL_image
animate.o: animate.cpp 
	g++ -c animate.cpp
fish.o: fish.h fish.cpp
	g++ -c fish.cpp

clean: 
	rm -f *.o fishtank