// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream> 

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);
/*
// Define an array of strings (an array of char pointers, like argv)
const char* wordBank[] = {
   "computer", "president", "trojan", "program", "coffee",
   "library", "football", "popcorn", "science", "engineer"};

const int numWords = 10;
*/

int main(int argc, char* argv[]) {
  srand(time(0));
  char guess[80];
  bool wordGuessed = false;
  int numTurns = 10;
  //Declaring an ifstream object
  ifstream ifile (argv[1]);
  if(ifile.fail())
  {
  	cout << "The file you entered could not be opened?" << endl;
  	return 1;
  }

  //Number of Words in the bank
  int numWords; 
  ifile >> numWords;
  if(ifile.fail())
  {
  	cout << "The first number in the file could not be read?" << endl;
  	return 1;
  }

  //Declaration of new array for wordbank.
  char** wordBank = new char*[numWords];

  //Buffer Array
  char buffer[41] = {};

  //Complicated
  for(int i = 0; i < numWords; i++)
  {
  	 //Create a buffer to put word into
  	 ifile >> buffer;
  	 //Check if it's ok
  	 if(ifile.fail())
  	 {
 		cout << "One of the strings couldn't be read?" << endl;
  		return 1;
  	 }
  	 //Create a place for this word to go on heap memory
  	 char* current_word = new char[strlen(buffer)];
  	 //Put buffer into the new char*
  	 strcpy(current_word,buffer);
  	 //Finally get the address of this pointer into the word bank;
  	 wordBank[i] = current_word;
  }
 



  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    wordGuessed = (strcmp(guess, wordBank[target]) == 0);
    numTurns--;
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }
  delete [] word; 
  delete [] wordBank;
  return 0;
}

// Scramble the letters. See "Knuth shuffle" on Wikipedia.
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}

