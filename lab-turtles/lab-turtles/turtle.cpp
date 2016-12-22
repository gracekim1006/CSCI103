#include "turtle.h"
#include "draw.h"
#include <iostream>
#include <cmath> 

using namespace std;

Turtle::Turtle(double x0, double y0, double dir0)
{
	x = x0;
	y = y0;
	direction = dir0;
	visible = true;
	//Setting color to black
	col.red = 0;
	col.blue = 0;
	col.green = 0;
}
//Turning the turtle
void Turtle::turn(double degrees)
{
	//Setting the turtles direction to the passed degree 
	//plus the current angle.
	direction += degrees;
}
//Moving the turtle with a line created.
void Turtle::move(double dist)
{

	double radians = (direction/180) * M_PI;
	//Where the turtle starts;
	double oldx = x;
	double oldy = y;
	//Setting turtle to new location
	//which builds off where it was last.
	x =  (dist*cos(radians) + oldx);
	y =  (dist*sin(radians) + oldy);
	//Drawing line only if the turtle is visible
	if(visible)
	{
		//Setting the color for draw to the current color of the turtle
		draw::setcolor(col.red, col.green, col.blue);
		draw::line(oldx, oldy, x, y);
	}
}
void Turtle::setColor(Color c)
{
	//Setting the drawcolor to what we want the turtle to be.
	draw::setcolor(c);
	//Additionally changing the data members of the turtle.
	col.red = c.red;
	col.blue = c.blue;
	col.green = c.green;
}
void Turtle::off()
{
	visible = false;
}
void Turtle::on()
{
	visible = true;
}
