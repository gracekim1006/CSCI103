#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

void sort(int *, int);
int binsearch(int, int *, int, int);
void swap(int *data, int dest, int source);

int main(int argc, char *argv[]){
  int target;
  if(argc < 2){
    cout << "Provide a filename of the data to be searched" << endl;
    return 1;
  }
  ifstream datfile(argv[1], ios::in);
  if( datfile.fail() ){
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }
  int count = 0;
  // Count how many integers are in the file
  while(! datfile.fail()){
    int temp;
    datfile >> temp;
    if(!datfile.fail()){
      count++;
    }
  }
  // When we reach the end of the file, the EOF flag is set
  // To be able to read through the file again we need to clear that flag
  datfile.clear();
  //  We also need to set our internal position in the file back to 0
  datfile.seekg(0,ios::beg);

  // Now allocate an array to store the file data and read in the data
  int *data = new int[count];
  for(int i=0; i < count; i++){
    datfile >> data[i];
  }

  datfile.close();

  cout << "Read " << count << " integers from the data file.\n" << endl;
  cout << "Enter the target positive integer to search for: ";
  cin >> target;

  // Uncomment the line below for part 2
  sort(data, count); 

  // Call binary search
  int retval = binsearch(target,data,0,count);

  // Interpret and print the results
  if(retval == -1){
    cout << target << " does not appear in the data." << endl;
  }
  else {
    cout << target << " appears at index " << retval << " in the data." << endl;
  }

  //Prints the list 
  //used for checking purposes 
  for(int i = 0; i < count; i++)
  {
      cout << data[i] << " ";
  }
  cout << endl;
  // Deallocate the data array
  delete [] data;
  return 0;
}


// Returns the index in the data array where target is located
//  or -1 if the target value is not in the list
int binsearch(int target, int *data, int start, int end)
{
	  //If we have gone through the entire method
	  //and we have finally reached target.
	  if(start == end)
    {
        if(data[start] == target)
        {
            return start;
        } 
        else
        {
            return -1;
        }
    }
		//Picks middle index we are going to use as 
		//a reference point.
		int midpoint = (start + end)/2;
		//If target is smaller than value at midpoint
		if(data[midpoint] > target)
		{
			//Don't include midpoint in next search
			return binsearch(target, data, start, midpoint - 1);
		}
		//If target is bigger than value at midpoint index
		else if(data[midpoint] < target)
		{
      //Don't include midpoint in next search
			return binsearch(target, data, midpoint + 1, end);
		}
		//If index at midpoint is equal to target.
		else		
			return midpoint;
}



// implements a selection sort algorithm to sort
//  the integer values in the 'data' array of size 'len'
// You aren't allowed to change the prototype of this function
void sort(int *data, int len)
{
  if(len == 1)
  {
      return;
  }
  else
  {
    //Declaration of needed variables for finding max
    int max = INT_MIN;
    int index_of_max;
    //Loops through to find the max
    for(int i = 0; i < len; i++)
    {
        if(data[i] > max)
        {
            max = data[i];
            index_of_max = i;
        }
    }
    //Puts Max at the end of the list.
    swap(data, index_of_max, len - 1);
    //Chops off len by one ignoring the number that 
    //was just placed in the end.
    sort(data, len - 1);
  } 
}
//Function that swaps two values in an array.
//Used in sort function to put largest number
//in the last spot of the array.
void swap(int* data, int dest, int source)
{
    int temp = data[dest];
    data[dest] = data[source];
    data[source] = temp;
}