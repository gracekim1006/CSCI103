#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {
   
   //Top line fill in
   for(int i = 0; i < width; i++)
   {
      //As long the indexes check out
      if(!(top > 255 || top < 0 || (i+left) > 255 || i+left < 0))
      {
         image[0 + top][i + left] = 0;
      }
   }
   //Bottom Line fill in
   for(int i = 0; i < width; i++)
   {
      //As long the indexes check out
      if(!(height+top > 255 || height+top < 0 || i+left > 255 || i+left < 0))
      {
         //Bottom line starts height away from top corner
         //Increments across columns
         image[0 + height + top][i+left] = 0; 
      }
   }
   //Left Line fill in
   for(int i = 0; i < height; i++)
   {
      //As long the indexes check out
      if(!(top+i < 0 || top+i > 255 || left > 255 || left < 0))
      {
         //Left line starts at TR,LC and increments down the rows
         image[0 + top + i][0 + left] = 0;
      }   
   }
   //Right Line fil in
   for(int i = 0; i  < height; i++)
   {
      if(!(top+i < 0 || top+i > 255 || left+width > 255 || left+width < 0))
      {
         //Right line starts at TR,LC+Width
         //Increments down the rows
         image[0 + top + i][0 + left + width] = 0;
      }
   }
}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {
   
   for(double theta = 0.0; theta < 2*M_PI; theta += 0.01)
   {
     int Rx = width/2;
     int Ry = height/2;
     double exact_x = Rx*cos(theta);
     double exact_y = Ry*sin(theta);
     int x = (int) exact_x + cx;
     int y = (int) exact_y + cy;
     //Check pixels are in range
     if(!(x < 0 || x > 255 || y < 0 || y > 255))
     {
        image[y][x] = 0;
     }
   }
}


int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }
   
   // Main program loop here
   cout << "To draw a rectangle, enter: 0" << endl;
   cout << "To draw an elipse, enter: 1" << endl;
   cout << "To save your drawing as \"output.bmp\" & quit enter: 2" << endl;
   int num, y, x, height, width;
   cin >> num;
   while(num != 2)
   {
      
      if(num > 2)
      {
         cout << "Not a valid value" << endl;
         num = 2; 
      }  
      if(num == 1)
      {
         cout << "Please enter the CR, CC, height and width: ";
         cin >> y >> x >> height >> width;
         draw_ellipse(y,x,height, width);
      }
      if(num == 0)
      {
         cout << "Please enter the TR, LC, height and width: ";
         cin >> y >> x >> height >> width;
         draw_rectangle(y,x,height,width);
      }
      cout << "Input 0 for rectangle, 1 for ellipse, or 2 to quit";
      cout << endl;
      cin >> num;
   }
   
   
   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);
   
   return 0;
}
