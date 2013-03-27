fishtank: main.o animate.o fish.o
	g++ main.o animate.o fish.o -o fishtank
main.o: main.cpp
	g++ -c main.cpp
animate.o: animate.cpp 
	g++ -c animate.cpp
fish.o: fish.h fish.cpp
	g++ -c fish.cpp

clean: 
	rm -f *.o fishtank