fishtank: animate.o fish.o
	g++ animate.o fish.o -o fishtank
animate.o: animate.cpp 
	g++ -c animate.cpp
fish.o: fish.h fish.cpp
	g++ -c fish.cpp

clean: 
	rm -f *.o fishtank