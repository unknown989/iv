all:
	g++ -std=c++17 -c main.cpp
	g++ -std=c++17 main.o -o iv -lsfml-graphics -lsfml-system -lsfml-window -Wall 

clean:
	rm main.o iv


.PHONY: install
install:
	install -m 557 ./iv /usr/bin
	mkdir -p /usr/share/iv/
	cp images/logo.png /usr/share/iv/icon.png
	cp iv.desktop /usr/share/applications
	cp iv.desktop ~/Desktop
