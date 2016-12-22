#include "draw.h"


class Turtle {
   public:
   Turtle(double, double, double);
   void move(double dist);
   void turn(double deg);
   void setColor(Color c);
   void on();
   void off();

   private:
   double x; 
   double y; 
   double direction;
   bool visible;
   Color col;
};