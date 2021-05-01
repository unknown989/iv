all:
	g++ -std=c++17 -c main.cpp 
	g++ -std=c++17 main.o -o iv -lsfml-graphics -lsfml-system -lsfml-window -Wall 

clean:
	rm main.o reader log.txt


.PHONY: install
install:
	install -m 557 ./iv /usr/bin
