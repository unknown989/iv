all:
	rm headers/jpeg.h.gch &
	g++ -std=c++17 -c main.cpp 
	g++ -std=c++17 main.o -o reader -lsfml-graphics -lsfml-system -lsfml-window -Wall 

old:
	rm headers/jpeg.h.gch &
	g++ -std=c++17 -c old.cpp jpeg/jpeg.h jpeg/jpeg.cpp -I/usr/include/libpng16 -ljpeg
	g++ -std=c++17 jpeg.o old.o -o oldreader -lsfml-graphics -lsfml-system -lsfml-window -lpng16 -ljpeg



clean:
	rm main.o reader jpeg.o log.txt creader old.o oldreader


install:
	rm headers/jpeg.h.gch &
	g++ -std=c++17 -c main.cpp 
	g++ -std=c++17 main.o -o iv -lsfml-graphics -lsfml-system -lsfml-window -Wall 
	mv ./iv /usr/bin/
