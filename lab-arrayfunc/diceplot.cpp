#include <iostream> 
#include <cstdlib> 
#include <ctime>
using namespace std;

int roll()
{
   int d1 = rand() % 6 + 1;
   int d2 = rand() % 6 + 1;
   int d3 = rand() % 6 + 1;
   int d4 = rand() % 6 + 1;
   int sum = d1 + d2 + d3 + d4;
   return sum;
}
void printHistogram(int counts[])
{
   //cycles through the rows of the histogram or indexes in arrays
   for(int i = 0; i < 21; i++)
   { 
      cout << i+4 << ":"; 
      for(int j = 0; j < counts[i]; j++)
      {
         cout << "X";
      }
      cout << endl; //Goes to the next line.
   }
}

int main()
{
   srand(time(0));
   //Prompt for use
   cout << "Please enter how many times to roll 4 dice: ";
   int number_of_trials;
   cin >> number_of_trials; 
   int results[21] = {0};
   int sum = 0;
   //loops through all the trials and collects sums
   for(int i = 0; i < number_of_trials; i++)
   {
      sum = roll();
      results[sum - 4]++;
      sum = 0;
   }
   printHistogram(results);
 
}


