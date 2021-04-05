
all:
	g++ -std=c++17 -c main.cpp jpeg/jpeg.h jpeg/jpeg.cpp -I/usr/include/libpng16 -ljpeg
	g++ -std=c++17 jpeg.o main.o -o reader -lsfml-graphics -lsfml-system -lsfml-window -lpng16 -ljpeg

clean:
	rm main.o reader jpeg.o log.txt


install:
	g++ -c main.cpp jpeg/jpeg.h jpeg/jpeg.cpp -I/usr/include/libpng16 -ljpeg
	g++ main.o jpeg.o -O3 -std=c++14 -o iv -lsfml-graphics -lsfml-system -lsfml-window -lpng16
	mv ./iv /usr/bin/
