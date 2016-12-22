// hangman.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn", 
                          "science", "engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;
  //const char* check = "*";

  // Pick a random word from the wordBank
  const char* targetWord = wordBank[rand() % numWords];
  // More initialization code as needed
  char word[80];  // a blank array to use to build up the answer
  int size = strlen(targetWord);  // It should be initialized with *'s and then
  for(int i = 0; i < size; i++)
  {
     strcpy(word+i, "*");
  }        
  cout << "Here is your word: " << word << endl; 
  cout << "You have ten turns (guesses) to complete the word.";
  cout << endl;
  cout << "If you guess correctly, it will not count as a turn";
  cout << endl;
  cout << "Good Luck" << endl;             
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while(!(wordGuessed) && numTurns > 0)
  {
     //Asks user to give a guess.
     cout << "Guess a character!" << endl;
     cin >> guess; 
     //Process whether guess was good. And changes stars to letters.
     int occurrences = processGuess(word, targetWord, guess);

     //Occurrences logic.
     if(occurrences > 1)
     {   
        cout << "Great guess!" << endl;
        cout << "There were " << occurrences << " occurrences of your guess!" << endl;
     }
     if(occurrences == 1)
     {
        cout << "Good guess!" << endl;
        cout << "There was " << occurrences << " occurrence of your guess!" << endl;
     }
     //If you didn't guess a correct letter, turn goes down.
     if(occurrences == 0)
     {
        cout << "Bad guess. Not in the word." << endl;
        numTurns--;
     }
     //Checks if you are done with the game
     if(strcmp(word, targetWord) == 0)
     {
        wordGuessed = true;
        //Put in break statement because I didn't want it to print # of turns if you won.
        break;
     }

     //Turn statement
     cout << numTurns << " turns remain...";
   }
  //If you guessed the word, congrats. End game status. 
  if(wordGuessed == true)
  {
     cout << "Congrats you guessed the word: " << targetWord << endl;
     cout << "Game Over. You won!" << endl;
  }
  else
  {
     cout << "The word was: " << targetWord << "." << endl;
     cout << "Game Over. You lose." << endl;
  }  

    
  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
    int occurrences = 0; 
    int size = strlen(targetWord);
    for(int i = 0; i < size; i++)
    {
       //Turns on any occurece of a correct guess.
       if(guess == targetWord[i])
       {
          occurrences++;
          word[i] = targetWord[i];
       }
    }
    cout << "Updated word: " << word << endl;
    return occurrences;

}

