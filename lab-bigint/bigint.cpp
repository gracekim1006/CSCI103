#include <string>
#include <vector> 
#include <iostream>
#include "bigint.h"
#include <stdlib.h> 

using namespace std;



BigInt::BigInt(string s)
{ 
	for(int i = 0; i < s.size(); i++)
	{
		int digit = (int) s[i];
		digit -= 48;
		//If you can print digits here for testing purposes
		integers.push_back(digit);
	}
}

string BigInt::to_string()
{
	//Empty String
	string str = "";
	//Iterating through vector and converting each number to char.
	for(int i = 0; i < integers.size(); i++)
	{
		char ch = (char) (integers[i] + 48);
		str += ch;
	}
	return str;
}

void BigInt::add(BigInt b)
{
	//How long the number is originally
	int bsize0 = b.integers.size();
	int asize0 = integers.size();

	
	//First make the vectors the same size if they are not.
	if(integers.size() < (b.integers).size())
	{
		while(integers.size() != (b.integers).size())
		{
			integers.push_back(0);
		}
		//Correcting the order
		for(int i = 0; i < asize0; i++)
		{
			int dig = integers[0];
			//Erases the firt element of vector, value is saved in dig.
			integers.erase(integers.begin());
			integers.push_back(dig);
		}

	}
	if(integers.size() > (b.integers).size())
	{
		while(integers.size() != (b.integers).size())
		{
			(b.integers).push_back(0);
		}
		//Correcting the order
		for(int i = 0; i < bsize0; i++)
		{
			int dig = b.integers[0];
			//Erases the firt element of vector, value is saved in dig.
			(b.integers).erase(b.integers.begin());
			(b.integers).push_back(dig);
		}
	}

	//cout << to_string() << endl;
	//cout << "B: " << b.to_string() << endl;

	//Now that alligning is done we have to do this part.
	//Creating a carry variable
	int carry;
	//digit to assign 
	int new_digit;
	//sum for two digits 
	int sum;
	
	for(int i = integers.size() - 1; i >= 0; i--)
	{
			//Adding the corresponding digit of each number
			sum = integers[i] + b.integers[i]; 
			//The digit is now equal to the ones digit of the sum.
			if(i != 0)
			{
				new_digit = sum % 10;
				//Assign the original vector with the new number
				integers[i] = new_digit;
				carry = sum / 10;
				integers[i-1] += carry;
			}
			else if(i == 0)
			{
				integers[i] = sum;
			}
			//Always should be one?
			//Unless it is the last one

	}
	//If the first index (last digit of the number) has more than one 
	//digit inside it
	if(integers[0] >= 10)
	{
		//Seperating the bigger digit and sending it to the back 
		//only to have everything sent to the back to follow.
		int size = integers.size() - 1;
		int tens = integers[0] / 10;
		int ones = integers[0] % 10;
		integers.push_back(tens);
		integers.push_back(ones);
		integers.erase(integers.begin());
		for(int i = 0; i < size; i++)
		{
			int dig = integers[0];
			//Erases the firt element of vector; value is saved in dig.
			integers.erase(integers.begin());
			integers.push_back(dig);
		}
	}
}