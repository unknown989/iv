all:
	g++ -c main.cpp -I/usr/include/libpng16
	g++ main.o -o reader -lsfml-graphics -lsfml-system -lsfml-window -lpng16

clean:
	rm main.o reader 


install:
	g++ -c main.cpp -I/usr/include/libpng16
	g++ main.o -O2 -o ir -lsfml-graphics -lsfml-system -lsfml-window -lpng16
	mv ./ir /usr/bin/