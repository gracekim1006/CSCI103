#include "network.h"
#include "user.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	string name = "Sandeep";
	int zip = 95070;
	int year = 1998;
	Network* facebook = new Network();
	facebook->add_user(name, year, zip);

	//Menu
	int input = 0;
	while(input <= 6 && input >= 0)
	{

		//Will be changed
		cout << "Please enter 1 to add user" << endl;
		cin >> input;
		if(input == 1)
		{
			string firstn;
			string lastn;
			int byear;
			int zipcode;
			cout << "Please enter first name" << endl;
			cin >> firstn;
			cout << "Please enter last name" << endl;
			cin >> lastn;
			cout << "Please enter birth year" << endl;
			cin >> byear;
			cout << "Please enter zipcode" << endl;
			cin >> zipcode;
			string username = firstn + " " + lastn;
			facebook->add_user(username, byear, zipcode);
			cout << username << endl;
		}
	}

}