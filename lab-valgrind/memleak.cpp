#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


// sum an array of numbers
int test1(int *data, int len)
{
  int sum = 0;
  //Change from "<= len" to "< len" because outside of array range
  for(int i=0; i < len; i++)
  {
    sum += data[i];
  }
  return sum;
}

// Allocate a random number array
//Removed parameters from the function
char* test2_init()
{
  char buf[80];
  cout << "Enter a word: ";
  cin >> buf;
  char* mydat = new char[strlen(buf)+1];
  strcpy(mydat, buf);
  return mydat;
}

char* test2_reverse(char* word)
{
  int len = strlen(word);
  char* otherword = new char[len+1];
  
  for(int i=0; i < strlen(word); i++){
    otherword[i] = word[len-i-1];
  }
  //Otherword len rather than len+1
  otherword[len] = '\0';
  delete [] word;
  return otherword;
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please enter the test number you want to run [1-2]" << endl;
    return 1;
  }
  const int len = 7;
  int test = atoi(argv[1]);

  if(test == 1){
    // Test should sum up the array values and print it
    
    int* data = new int[len];
    for(int i=0; i < len; i++){
      data[i] = rand()%100;
    }
    int sum = test1(data, len);
    cout << "Test 1 sum is " << sum << endl;
    delete [] data;
  }

  else if(test == 2){
    // Test should create a random string & then reverse a copy
    /*
    Previosly we had this code "char* myword = test2_init(len);"
    So I changed the function parameters to not include test2_init(len).
    */
    char* myword = test2_init();
    cout << "myword is " << myword << endl;
 
    char* otherword = test2_reverse(myword);    
    cout << "otherword is " << otherword << endl;
    
    //Got rid of deleteing myword because it is not new.
    //delete [] myword;
    delete [] otherword;
  }
  else {
    cout << "Unknown test number" << endl;
  }

  return 0;
}
