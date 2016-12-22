/*********************************************************
 * File name : tp.cpp
 * Author    : Sandeep Suresh
 * Date      : 09/17/16
 * Purpose   : Simulates the toilet-paper problem
 * Notes     : None
 *********************************************************/

#include <iostream>   // Basic I/O => cin, cout, etc.
#include <cstdlib>
#include <ctime>    // Other helpful functions => rand(), RANDMAX

using namespace std;

// Prototype/declaration of a function that returns a
// uniform random number between [0,1]
double rand_uniform();

// Prototype/declaration of a function that will perform a single
// simulation of two rolls of paper and users
// Returns the number of squares left on the non-empty roll
int single_sim(int N, double p);

int main(int argc, char *argv[])
{
  //seeds rand function
  srand(time(0));
 

  int N;                // initial number of squares on each roll
 
  double p;             // probability of a big-chooser
 
  int sims;             // number of trials for our simulation


  cout << "Please enter the amount of squares, probability, and trial #" << endl;

  cin >> N >> p >> sims;
  //checks if values are ok
  if(N <= 0 || p < 0 || sims <= 0 || p > 0)
  {
     cout << "You didn't enter a valid input!" << endl;
     return 0;
  }
  /*
  Variable used to total up all remainders of toilet paper for
  all simulations.
  */
  int total_leftovers = 0;

  for(int i = 0; i < sims; i++)
  {
      //Add remainders to total sum
      total_leftovers += single_sim(N, p);
  }
  //divide sum by # of sims to get the average
  double avg = total_leftovers * 1.0 / sims;


  cout << "Average: " << avg << endl;

  // Be sure you produce an output of the form:
  // Average: 1.2314
  // where the number is the correct average

  return 0;
}

// return the number of squares on the non-empty roll
//  for this simulation of the problem
int single_sim(int N, double p)
{
   //Set roll lengths equal to N.
   int roll1 = N;
   int roll2 = N;
   //While neither roll is empty
   while(roll1 != 0 && roll2 != 0)
   {
      //Patron represents person with value from [0,1] 
   	double patron = rand_uniform();
      if(roll1 == roll2)
      {
        roll1--;       
      }
      //If person is a big roll chooser.
      else if (patron <= p)
      {
        //Determine which is bigger and take.
        if (roll1 > roll2)
        {
           roll1--;
        }
        else 
        {
           roll2--;
        }         
      }
      //If person is a small roll chooser
      else if(patron > p)
      {
         if(roll1 > roll2)
         {
            roll2--;
         }
         else
         {
            roll1--;
         }
      }
      
   }
   //Return the roll that is not empty
   if(roll1 == 0)
    return roll2;
   return roll1;
}

// returns a uniformly-distributed number in the range [0,1]
//  The caller can use the return result to then determine
//  if it should treat it as a big- or little-chooser by 
//  also using the p parameter.  This code only needs to 
//  produce a random number in the range [0,1]
double rand_uniform()
{
   return rand() * 1.0 / RAND_MAX;
}
