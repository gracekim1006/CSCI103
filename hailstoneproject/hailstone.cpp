/*
Sandeep Suresh
Email: surehsa@usc.edu
USC ID# 7720774451
Date started: 09/04/16
Description: This program uses a loop to determine how many steps will 
it take for a number to reach one as it goes through an algorithm. The 
algorithm entails that if a number is odd it gets multiplied by 3 then
increased by 1. If the number is even, it gets halved. This process
continues until the number becomes one. This alogrithm is also called the 
hailstone algorithm.
*/

#include <iostream>
using namespace std;

int length = 0;

int hailstone(int x)
{
  if(x == 1)
    {
      return length;
    }
  if(x % 2 == 0)
    {
      length++;
      return hailstone(x/2);
    }
  else 
    {
      length++;
      return hailstone(x*3 + 1);
    }
}

int main()
{
  //Prompts the user to enter a number to go through the algorithm
   cout << "Please enter a number to go through the Hailstone algorithm: ";
   int num;
   cin >> num;
   // int length = 0; 
   cout << "Length: " << hailstone(num) << endl;
  

  
   //While the number isn't one yet, we keep going through the alogrithm
   /*
   while(num != 1)
   {
      //If the number is even we divide by 2 and print out the number
      if(num % 2 == 0)
      {
         num /= 2; 
         cout << num << " ";
	 
      }
*/
      /*
      If the number is odd then we multiply by 3 and add 1, then print  
      out the number.
      */
   /*
      else
      {
         num = num*3 + 1;
	      cout << num << " ";
      }
      length++;
   }
   */

   //End line after all numbers have been printed out. 
   cout << endl;
   //Prints the results
   cout << "Length: " << length << endl;
   return 0;
}
