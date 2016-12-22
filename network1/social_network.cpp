#include "network.h"
#include "user.h"
#include <iostream> 
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
	Network* facebook = new Network();
	facebook->read_friends(argv[1]);
	//Menu
  	int input = 0;
  	while(input <= 6 && input >= 0)
	{
		cout << "Menu options are as follows:" << endl;
		cout << "1: to add a new user!" << endl;
		cout << "2: to add a friend connection" << endl;
		cout << "3: to remove a friend connection" << endl;
		cout << "4: to print a list of users and their info" << endl;
		cout << "5: to list all friends of a user" << endl;
		cout << "6: to write all user info to a file" << endl;
		cout << "Press any other number to quit" << endl;
		cin >> input;
		//If we want to add a user.
		if(input == 1)
		{
			string firstn;
			string lastn;
			int byear;
			int zipcode;
			cout << "Please enter full name" << endl;
			cin >> firstn;
			cin >> lastn;
			cout << "Please enter birth year" << endl;
			cin >> byear;
			cout << "Please enter zipcode" << endl;
			cin >> zipcode;
			string username = firstn + " " + lastn;
			facebook->add_user(username, byear, zipcode);
		}
		//Adding a friend connection
		else if(input == 2)
		{
			cout << "Please enter both full names" << endl;
			//Storing names
			string fname1;
			string fname2;
			string lname1;
			string lname2;
			string username1;
			string username2;
			//Getting names
			cin >> fname1;
			cin >> lname1;
			cin >> fname2;
			cin >> lname2;
			//Setting usernames
			username1 = fname1 + " " + lname1;
			username2 = fname2 + " " + lname2;
			//Adding the connection
			//This will also check if these names are valid
			facebook->add_connection(username1, username2);
		}
		//Removing friends
		else if(input == 3)
		{
			cout << "Please enter both full names" << endl;
			//Storing names
			string fname1;
			string fname2;
			string lname1;
			string lname2;
			string username1;
			string username2;
			//Getting names
			cin >> fname1;
			cin >> lname1;
			cin >> fname2;
			cin >> lname2;
			//Setting usernames
			username1 = fname1 + " " + lname1;
			username2 = fname2 + " " + lname2;
			//Adding the connection
			//This will also check if these names are valid
			facebook->remove_connection(username1, username2);
		}
		else if(input == 4)
		{
			facebook->print_users();
		}
		else if(input == 5)
		{
			//Getting the name of the user
			cout << "Please enter the full name of the user to see all friends";
			cout << endl;
			string fname;
			string lname;
			string username;
			cin >> fname;
			cin >> lname;
			username = fname + " " + lname;
			facebook->printUserFriends(username);

		}
		//Writing to a file 
		else if(input == 6)
		{
			cout << "Please enter a filename for your output" << endl;
			string outfile;
			cin >> outfile;
			const char* ofile = outfile.c_str();
			facebook->write_friends(ofile);
		}
	}
	delete facebook;
}
