/*
Owner : Brian Polier
Years : 2020-2021
Date : 29-03-2021
Description : This is a PNG Image Viewer that has the basic features ,for more informations read the ./Usage
=================================================================================
= This software is under The GNU GPL v3 license which can be found on ./LICENSE =
=================================================================================
*/

#include <png++/png.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iomanip>

#include "jpeg/jpeg.h"
#include "headers/filedetection.hpp"

using namespace std;

void readPNG(string filename,uint32_t &height,uint32_t &width,sf::Image *img){
	
	// Read the image
	png::image<png::rgb_pixel> image(filename);
	height = image.get_height(); // Height 
	width = image.get_width(); // width
    img->create(width,height); // Create an sf::Image with the same dimensions as the png::image() image;

    for(int x = 0;x < width;x++){
        for(int y = 0;y < height;y++){
            img->setPixel(x,y,sf::Color(image.get_pixel(x,y).red,image.get_pixel(x,y).green,image.get_pixel(x,y).blue)); // Get the RGB values of x,y in the image and load them to the image
        }
    }
}
void readJPG(string filename,uint32_t &height,uint32_t &width,sf::Image *img){
	marengo::jpeg::Image image(filename);
	height = (uint32_t)image.getHeight();
	width = (uint32_t)image.getWidth();
	img->create(width,height);
	for(int x = 0;x < width;x++){
	        for(int y = 0;y < height;y++){
	        	vector<uint8_t> pixel = image.getPixel(x,y);
	            img->setPixel(x,y,sf::Color(pixel[0],pixel[1],pixel[2])); // Get the RGB values of x,y in the image and load them to the image
	   		}
	}
}

int main(int argc,char** argv){
    bool resizeRect = false;
	if(argc < 2){
        std::cout << "./reader [filename].png" << std::endl;
        return 1;
	}
	cout << "Filename : " << argv[1] << endl;
	uint32_t height,width;
    int winH = 600; // Window Height
    int winW = 800; // Window Width

    sf::Image* img = new sf::Image();

	// Render the PNG Image
	string detectionres = detect(argv[1]); // File Format Detection result	
	if( detectionres == "PNG"){
		cout << "Detected a PNG File Format" << endl;
		readPNG(string(argv[1]),height,width,img);
	}else if(detectionres == "JPEG"){	
		cout << "Detected a JPEG File Format" << endl;
		readJPG(string(argv[1]),height,width,img);
	}else{
		cout << "File Format/Type is not supported yet" << endl;
	}

	sf::RenderWindow app(sf::VideoMode(winH,winW),"ir : Image Reader"); // Window initialization


    sf::Texture* t;
    t->loadFromImage(*img); // Load a texture with the img
    sf::RectangleShape rect; 
    rect.setSize(sf::Vector2f(width,height)); // Make a rectangle with the width and height of the image
    rect.setTexture(t);
    rect.setOrigin({rect.getSize().x/2,rect.getSize().y/2}); // Setting the origin to the center
	rect.setPosition({0,0}); // Setting the rectangle to the center of the screen
	
    int mouseOldX = sf::Mouse::getPosition().x; // Mouse Previous X
    int mouseOldY = sf::Mouse::getPosition().y; // Mouse Previous Y
    int xMouseSpeed  = 1; // Mouse Speed at X
    int yMouseSpeed  = 1; // Mouse Speed at Y
    int xDelta = 0; // XDelta (check if the mouse cursor is going right or left)
    int yDelta = 0; // YDelta (check if the mouse cursor is going up or down)
    float zoom = 1; // Zooming value
	// float zoomDelta = 1; // Variable to make the mouse slower when zooming in
	
	while(app.isOpen()){
        sf::Event event;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            int mouseCurrentX = sf::Mouse::getPosition(app).x; // The current X of the mouse cursor
            int mouseCurrentY = sf::Mouse::getPosition(app).y; // The Current Y of the mouse cursor
            xDelta = 0;
            yDelta = 0;
            xMouseSpeed = abs(mouseCurrentX - mouseOldX); // Get the speed of the cursor by taking the absolute value of the substraction of current X of the mouse and the previous X
            yMouseSpeed = abs(mouseCurrentY - mouseOldY); // Same thing but the Y values |x - oldX|
            if(mouseCurrentX > mouseOldX){
                xDelta = 1; // if x if bigger than oldX that means the mouse is moving to right
            }
            else if(mouseCurrentX < mouseOldX){
                xDelta = -1; // opposite
            }
            else{
                xDelta = 0; // Not moving any where
            }

            if(mouseCurrentY > mouseOldY){
                yDelta = 1; // Same as the first but with Y values
            }
            else if(mouseCurrentY < mouseOldY){
                yDelta = -1; // Same as the second but with Y values
            }
            else{
                yDelta = 0; // Same as the third but with Y values
            }

            mouseOldX = mouseCurrentX; // Set oldX to x
            mouseOldY = mouseCurrentY; // set oldY to y
        }

        while (app.pollEvent(event))
        {
            if(event.type == sf::Event::Resized){
                resizeRect = true;
            }
            if(event.type == sf::Event::MouseButtonReleased){
                xMouseSpeed = 1; // If the mouse button is released we set the speed of both x & y to 1
                yMouseSpeed = 1;
            }else if(event.type == sf::Event::MouseButtonPressed){
            int mouseCurrentX = sf::Mouse::getPosition(app).x; // Same the previous movement method
            int mouseCurrentY = sf::Mouse::getPosition(app).y;
            xMouseSpeed = abs(mouseCurrentX - mouseOldX);
            yMouseSpeed = abs(mouseCurrentY - mouseOldY);
            }
            if(event.type == sf::Event::MouseWheelMoved)
            { // Zooming system
                int delta = event.mouseWheel.delta; // Direction of the mouse wheel (up,down)
                if(delta < 0 && ((0 < zoom) && (zoom < 4))){ // if the wheel is going up and the zoom isn't in the max and the min zoom in by 0.1
                    zoom -= 0.1;
                }else if(delta > 0 && ((0 < zoom) && (zoom < 4))){ // vice-versa
                    zoom += 0.1;
                }
                // Pretty stupid but c++ behave weirdly
                if(zoom >= 4){ // just getting the zoom back to its limits
                zoom = 3.9;
                }
                if(zoom <= 0){
                zoom = 0.1;
                }

            }
            if (event.type == sf::Event::Closed){
                app.close();
                exit(0);
            }
        }
        rect.move({xDelta*(float)xMouseSpeed,yDelta*(float)yMouseSpeed});// Moving the rectangle that holds the texture now using the x and y delta and the x,y speed

        app.clear(sf::Color::White);
        app.setView(sf::View(sf::Vector2f(0,0),sf::Vector2f(app.getSize().x*zoom,app.getSize().y*zoom))); // Setting the sf::View for implementing the zooming ability by adjust the size of the view : multiplying it by the zoom value
        app.draw(rect);

        app.display();
	}
	return 0;
}
