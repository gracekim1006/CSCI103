#include <iostream> 
#include <cmath>
using namespace std; 

int main()
{
  //input for angle in double form
  double angle;
  cout << "Please give an angle value you want between 15 and 75 (please include decimal place): " << endl;
  cin >> angle;

  //Conversion of angle to radians
  angle = angle * M_PI/180;

  //Ratio determined to find how many x's per h.
  double ratio = tan(angle);

  //
  

  for(int h = 0; h < 31; h++)
  {
    cout << endl;
    for(int i = 0; i < (int) floor(h*ratio); i++)
    {
      //If the number of approximated stars is greater than 20 or less than 30
      if( (int) floor(h*ratio) >= 20 && (int) floor(h*ratio) <= 30 && i == 20)
	      break;
      cout << "*";
    }
  }
  cout << endl;
}
