#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
   // Enter your code here
  cout << "Please enter three values for the components of Red, Green, and Blue, ranging from 0 to 255." << endl;
  int red;
  int green;
  int blue;
  cin >> red >>  green >>  blue; 
  //Note to self: Create code later that doesn't accept any value outside of the range.
  if(red > 255 || red < 0)
  {
    cout << "This value is not in the range accepted!" << endl;
    return 0;
  }
  if(green > 255 || green < 0)
  {
    cout << "This value is not in the range accepted!" << endl;
    return 0;
  }
  if(blue > 255 || blue < 0)
  {
    cout << "This value is not in the accepted range!" << endl;
    return 0;
  }
  //Defining white
  double  white; 
  int temp_max = max(red, green);
  int true_max = max(temp_max, blue);
  white = true_max/255.0;

  //Defining Cyan
  double cyan = (white - red/255.0)/white;
  
  //Defining Magenta
  double magenta = (white - green/255.0)/white;

  //Defining Yellow
  double yellow = (white - blue/255.0)/white;

  //Defining Black
  double black = 1.0 - white;

  //Outputting the results of the program
  cout << "cyan: " << cyan << endl;
  cout << "magenta: " << magenta << endl;
  cout << "yellow: " << yellow << endl;
  cout << "black: " << black << endl;

   return 0;
}
