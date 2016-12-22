/*
Name: Sandeep Suresh 
USC ID# 7720774451
Date: 08/31/16n
*/
#include <iostream>
#include <cmath>
using namespace std;

int main(){
   cout << "Please enter an integer between 0 and 999!" << endl;
   int input;
   cin >> input;
   /* 
   //Declaring variables for each digit
   int ones;
   int tens;
   int hundreds;

   //Initliazing the ones variable
   ones = input % 10;
   
   //Initializing the tens variable
   tens = (input / 10) % 10;
   
   //Initializing the hundreds variable
   hundreds = input / 100; 
   
   //Printing Results
   cout << "1's digit is: " << ones << endl;
   cout << "10's digit is: " << tens << endl; 
   cout << "100's digit is: " << hundreds << endl;
*/

   //Method to find the digits of any number

   //temporary storage for each digit
   int temp;

   //exponent power that needs to keep incrementing
   int count = 0;

   //Number to printed out for the correct digit (ex. 1's, 10's, 100's)
   int digit = 1;

   while((input/ (int) pow(10, count))!= 0)
   { 
     temp =((input / (int) pow(10,count))) % 10; 
     cout << digit << "'s digit is: " << temp << endl;
     count++;
     digit = pow(10,count);
   }
}
