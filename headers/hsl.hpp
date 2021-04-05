#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int maximum(int x, int y, int z) {
	int max = x; /* assume x is the largest */

	if (y > max) { /* if y is larger than max, assign y to max */
		max = y;
	} /* end if */

	if (z > max) { /* if z is larger than max, assign z to max */
		max = z;
	} /* end if */

	return max; /* max is the largest value */
} /* end function maximum */

int minimum(int x, int y, int z) {
	int min = x;
	if (y < min) {
		min = y;
	}
	if (z < min) {
		min = z;
	}
	return min;
}

sf::Color RGBtoHSL(sf::Color c){
	float r,g,b;
	r = (c.r/255);
	g = (c.g/255);
	b = (c.b/255);
	// Min and Max
	float max = maximum(r,g,b);
	float min = minimum(r,g,b);
	// Luminance
	float l = (max+min)/2;
	// Saturation
	float s;
	if(max == min){s = 0;}
	else if(l < 0.5){ s = (max-min)/(max+min);}
	else if(l > 0.5){s = (max - min)/(2-max-min);}
	else{s = 0;}
	// Hue
	float h;
	if( r == max){h = (g-b)/(max-min);}
	else if(g == max){ h = 2+(b-r)/(max - min);}
	else{ h = 4+(r-g)/(max - min);}
	
	return sf::Color((int)h,(int)s,(int)l);
	
}

