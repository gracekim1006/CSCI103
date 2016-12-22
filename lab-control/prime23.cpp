#include <iostream> 
using namespace std; 

int main() 
{

   //Taking the integer.
   int num;
   cout << "Enter a positive integer: " << endl; 
   cin >> num; 

   if(num < 2)
   {
     cout << "You have entered an interesting number. I'm sorry this is not an accepted value." << endl;
     return 0;
   }   
   int threes_count = 0;
   int twos_count = 0;
   
 
      if(num % 2 != 0 && num % 3 != 0)
      {
         cout << "No" << endl;
	      return 0;
      }
      if(num % 2 == 0)
      {
         while(num % 2 == 0)
         {
            num /= 2;
            twos_count++;
	 }
      }
      if(num % 3 == 0)
      {
         while(num % 3 == 0)
         {
            num /= 3;
            threes_count++;
         }
      }
      if(num > 1) cout << "No" << endl;
      
      if(num == 1)
      {
	cout << "Yes" << endl;
	cout << "Twos=" << twos_count << " "; 
	cout << "Threes=" << threes_count << endl;
      }
      return 0;
}
