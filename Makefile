all:
	g++ -std=c++17 -c main.cpp 
	g++ -std=c++17 main.o -o reader -lsfml-graphics -lsfml-system -lsfml-window -Wall 

clean:
	rm main.o reader log.txt


install:
	g++ -std=c++17 -c main.cpp 
	g++ -std=c++17 main.o -o iv -lsfml-graphics -lsfml-system -lsfml-window -O3 
	mv ./iv /usr/local/bin/
