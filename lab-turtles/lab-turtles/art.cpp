#include "draw.h"
#include "turtle.h"
#include <iostream> 
#include <ctime>
#include <cstdlib>

using namespace std; 

int main()
{
	srand(0);
	//set corners
	draw::setrange(-100,100);
	//Instances of Turtles
	Turtle leonardo(10,10,0);
	Turtle raphael(-10,10,90);
	Turtle donatello(-10,-10,180);
	Turtle michaelangelo(10,-10,270);

	//Setting different colors for each
	leonardo.setColor(draw::CYAN);
	//Setting the color
	raphael.setColor(draw::BLUE);
	//Setting the color
	donatello.setColor(draw::RED);
	//Setting the color
	michaelangelo.setColor(draw::GREEN);

	//Squares
	for(int i = 0; i < 4; i++)
	{
		leonardo.move(80);
		leonardo.turn(90);
		draw::show(500);
		raphael.move(80);
		raphael.turn(90);
		draw::show(500);
		donatello.move(80);
		donatello.turn(90);
		draw::show(500);
		michaelangelo.move(80);
		michaelangelo.turn(90);
		draw::show(500);
	}
	return 0;

}