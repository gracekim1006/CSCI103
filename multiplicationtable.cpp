#include <iostream> 
#include <iomanip>
using namespace std;

int main()
{
   for(int r = 1; r <= 25; r++)
   {
      for(int c = 1; c <= 25; c++)
      {
         cout << setw(4) << r*c;     
      }
      cout << endl;
   }  
}
