#include <iostream>
#include <cmath>

/* Author: Sandeep Suresh
 * Program: compute_sin
 * Description: Reads a number x from input, an angle in radians. 
 *    Computes an approximation to sin(x) using an 4th-order Taylor series.
 */

using namespace std;

int fact(int); // declares a function the skeleton defines for you.

int main(int argc, char *argv[])
{
   // Declare any variables you need here
   
   
   // Prompt the user
   cout << "Enter x in radians:  ";
   
   // get input
   double radians;
   cin >> radians;
   
   // Do some operations
   double solution = radians - (pow(radians, 3.0)/fact(3.0))+(pow(radians, 5.0)/fact(5.0))-(pow(radians, 7.0)/fact(7));
   
   // Print the result to the user
   cout << solution << endl; 
   
   // You're done
   return 0;
   
}

// here's the actual definition of fact, declared earlier.
int fact(int n)
{
   int result = 1;
   for (int i = 1; i <= n; i++) {
      result = result * i;
   }
   return result;
}

