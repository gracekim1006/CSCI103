/* Sandeep Suresh 
Email: sureshsa@usc.edu
USC ID# 7720774451
Description: This program uses the hailstone function
to determine the number of steps it takes for a number
to reach 1. This program uses said fuction to cycle 
through a range of numbers inputted by the user and 
determines which is the minimum legnth achieved by
a number and the maximum legnth achieved by a number.
*/

#include <iostream>
#include <climits> 
using namespace std; 

//Function that does the hailstone algorithm
int hailstone(int x)
{
  int length = 0;
  while(x != 1)
  {
    //If even divide by two
    if(x % 2 == 0)
    {
      x /= 2;
      length++;
    }
    //If odd multiply by 3 add one
    else
    {
      x = x*3 + 1;
      length++;
    }
  }
  return length; 
}

int main()
{
  //The minimum and maximum legnths, and the inputs the computer needs.
  int min_length = INT_MAX;
  int max_length = 0;
  cout << "Enter the range you want to search: ";
  int lower_limit;
  int upper_limit;
  cin >> lower_limit >> upper_limit;
  if(lower_limit > upper_limit || lower_limit <= 0 || upper_limit <= 0)
  {
    cout << "Invalid range" << endl;
    return 0;
  }
  /*
  If the lower limit is equal to the upper limit then assign
  all values to the number given. 
  */
  if(lower_limit == upper_limit)
  {
    min_length = hailstone(lower_limit);
    max_length = hailstone(upper_limit);
    cout << "Minimum length: " << min_length << endl;
    cout << "Achieved by: " << lower_limit << endl;
    cout << "Maximum length: " << max_length << endl;
    cout << "Achieved by: " << upper_limit << endl;
    return 0; 
  }
  //The 
  int min;
  int max;
  int temp;
  //Cycles through all the values
  for(int i = lower_limit; i <= upper_limit; i++)
  {
     temp = hailstone(i);
     if(temp < min_length)
     {
        min = i;
        min_length = temp;
     }
     if(temp > max_length)
     {
        max = i;
        max_length = temp;
     }
     /*
     if(temp > 150)
      cout << "There is a number here!\n";
      */
  }
  cout << "Minimum length: " << min_length << endl;
  cout << "Achieved by: " << min << endl;
  cout << "Maximum length: " << max_length << endl;
  cout << "Achieved by: " << max << endl;
  return 0;
}

