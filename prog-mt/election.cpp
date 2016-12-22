#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
// You may add #includes in this program

using namespace std;

// Stores a state's name and how many
// electoral votes that state has
struct StateElectoralInfo{
  string state;
  int elecVotes;
};

// Complete the following function
//
// This function should search/find the target stateName
//  in an array of StateElectoralInfo structs
//  and return that state's electoral vote number
//
//  state_info  input array of filled in StateElectoralInfo structs
//  len         is the length/size of the state_info array
//  stateName   is the state name you need to find
//
// Return the electoral votes the target state has
// Return -1 if the stateName does not appear in the array

int getStateElecVotes(StateElectoralInfo state_info[], int len,string stateName)
{
  // Add your code here
  //Loop through the states
  for(int i = 0; i < len; i++)
  {
    if(state_info[i].state == stateName)
    {
        return state_info[i].elecVotes;
    }
  }
  return -1;

}


//**************************************
// Do not change these 2 lines and don't
// add any lines between them and main()
//**************************************
#ifndef AUTO_TEST
#define AUTO_TEST
int main(int argc, char* argv[])
{
  //*********************************************************
  // Use these declarations to store the appropriate answers.
  // Our 'couts' at the bottom expect these variables to 
  //  be set correctly by the end of your program.
  //*********************************************************
  string candidate1; // Store candidate 1 last name here
  string candidate2; // Store candidate 2 last name here

  int c1_electoral_votes=0; // Total (all states) candidate 1 electoral  votes
  int c2_electoral_votes=0; // Total (all states) candidate 1 electoral  votes

  int c1_total_votes=0; // Total candidate 1 popular votes from all states
  int c2_total_votes=0; // Total candidate 2 popular votes from all states
  
  string best_c1_state; // State with highest percentage win for candidate1
  string best_c2_state; // State with highest percentage win for candidate2

  double best_c1_percent = 0.0; // Store highest percentage of vote candidate1 
                                //  got in a state
  double best_c2_percent = 0.0; // Store highest percentage of vote candidate2 
                                //  got in a state


  if(argc < 3){
    cout << "Not enough command line arguments." << endl;
    cout << "Usage: ./election <electoral college data file> <voting data file>"
	 << endl;
    return -1;
  }

  // cout this message if the program fails to open the electoral file
  const string elecFileErrorMsg = "Electoral college file not found.";
  // cout this message if the program fails to open the voter file
  const string voterFileErrorMsg = "Voter totals file not found.";

  //*********************************************************
  // Write your code below to perform the overall task.
  // Be sure to follow requirements.  Make sure your code
  // produces the appropriate values of the variables we
  // declared above so that the code at the bottom will print
  // out the answers in the correct format.
  //*********************************************************

  //Insert names to be something
  //Stream opened
  ifstream ifile1 (argv[2]);
  if(ifile1.fail())
  {
    cout << "A file could not be read!" << endl;
    return 1;
  }
  ifile1 >> candidate1;
  if(ifile1.fail())
  {
    cout << "A candidate name could not be read!" << endl;
    return 1;
  }
  ifile1 >> candidate2;
  if(ifile1.fail())
  {
    cout << "A candidate1 name could not be read!" << endl;
    return 1;
  }


  //Stream opened
  ifstream ifile (argv[1]);
  //Fail Check
  if(ifile.fail())
  {
    cout << "A file could not be read!" << endl;
    return 1;
  }

  //Number of states
  int num_of_states;
  ifile >> num_of_states;
  if(ifile.fail())
  {
        cout << "Number of states could not be read" << endl;
        return 1;
  }

  //Creating an array to store all States 
  //array is of type StateElectoralInfo
  //with length of what the files says
  StateElectoralInfo* array_of_states = new StateElectoralInfo[num_of_states];

  //Reading all files info into the array
  for(int i = 0; i < num_of_states; i++)
  {
      //Reading in name of state
      ifile >> array_of_states[i].state;
      if(ifile.fail())
      {
          cout << "State name could not be read!" << endl;
          return 1;
      }
      //Reading in number of electoral votes
      ifile >> array_of_states[i].elecVotes;
      if(ifile.fail())
      {
          cout << "Number of votes for state could not be read!" << endl;
          return 1;
      }
  }

  //Reading in the votes of the people for each state.
  //Additionally calculating the best states for candidates
  for(int i = 0; i < num_of_states; i++)
  {
    //Popular vote numbers for current state 
    int popularVotesForCand1;
    int popularVotesForCand2;

    //Reading in votes for each candidate
    ifile1 >> popularVotesForCand1;
    if(ifile1.fail())
    {
          cout << "Number of votes for state could not be read!" << endl;
          return 1;
    }
    ifile1 >> popularVotesForCand2;
    if(ifile.fail())
    {
         cout << "Number of votes for state could not be read!" << endl;
         return 1;
    }

    //Increasing Total Votes
    c1_total_votes += popularVotesForCand1;
    c2_total_votes += popularVotesForCand2;

    //Total votes for state
    int total_votes_of_state = popularVotesForCand1 + popularVotesForCand2;

    //Getting current state name
    string current_state = "";
    ifile1 >> current_state;
    if(ifile1.fail())
    {
        cout << "Could not read state" << endl;
        return 1;
    }

     //Getting the number of elector votes for the current state;
    int num_of_evotes = 
        getStateElecVotes(array_of_states, num_of_states, current_state);

    //Assigning electoral votes to the candidate who won
    if(popularVotesForCand1 > popularVotesForCand2)
    {
        c1_electoral_votes += num_of_evotes;
    }
    else 
    {
        c2_electoral_votes += num_of_evotes;
    }

    //Percentages 
    double percentage_for_c1 = popularVotesForCand1*1.0/total_votes_of_state;
    double percentage_for_c2 = popularVotesForCand2*1.0/total_votes_of_state;
    if(percentage_for_c1 > best_c1_percent)
    {
        best_c1_state = current_state;
        best_c1_percent = percentage_for_c1;
    }
    if(percentage_for_c2 > best_c2_percent)
    {
        best_c2_state = current_state;
        best_c2_percent = percentage_for_c2;
    }

  }














  
  //**************************************
  // You are DONE!  The code below this point
  //  will use the values in the variables
  //  declared at the top of main to output
  //  the desired statistics to the screen.
  //**************************************
  string winner;
  string loser;
  int w_electoral;
  int l_electoral;
  int w_total;
  int l_total;
  if(c1_electoral_votes > c2_electoral_votes)
    {
      winner = candidate1;
      loser = candidate2;
      w_electoral = c1_electoral_votes;
      l_electoral = c2_electoral_votes;
      w_total = c1_total_votes;
      l_total = c2_total_votes;
    }
  else
    {
      winner = candidate2;
      loser = candidate1;
      l_electoral = c1_electoral_votes;
      w_electoral = c2_electoral_votes;
      l_total = c1_total_votes;
      w_total = c2_total_votes;
    }
  
  cout << winner << " defeated " << loser 
       << " in the electoral college." << endl; 

  cout << "The electoral vote count was " << w_electoral
       << " votes to " << l_electoral << " votes." << endl;
  
  cout << "The popular vote total was " << w_total << " to " << l_total << endl;
  
  cout << winner << "'s best state was " << best_c1_state << " where they won ";
  cout  << 100*best_c1_percent << " percent of the votes" << endl;
  
  cout << loser << "'s best state was " << best_c2_state << " where they won "; 
  cout << 100*best_c2_percent << " percent of the votes" << endl;
  
  delete [] array_of_states;
  return 0;  
}
//****************************************
// Do not change the following line
//****************************************
#endif

//****************************************
// You may add code after this if you like
//****************************************
