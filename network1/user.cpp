#include <string>
#include <iomanip>
#include <vector> 
#include <iostream>
#include "user.h"
#include <cstdlib>

using std::string;
using std::vector;
using namespace std;

User::User(string uname, int idnum, int year, int zcode)
{
 	id = idnum;
 	birth_year = year;
 	zip = zcode;
 	name = uname;
}
void User::add_friend(int idnum)
{
	for(int i = 0; i < friends.size(); i++)
	{
		//If the friend is already on your friends list, do nothing.
		if(friends[i] == idnum)
		{
			return;
		}
	}	
	//If the for loop runs entirely then, push back the id number. 
	friends.push_back(idnum);	
}

void User::delete_friend(int idnum)
{
	int index_of_id = -1;
	for(int i = 0; i < friends.size(); i++)
	{
		if(friends[i] == idnum)
		{
			index_of_id = i;
		}
	}
	//If the id was not found in the list, do nothing.
	if(index_of_id == -1)
	{
		cout << "The friend you were looking for is not in your list" << endl;
	}
	//If the id was found erase the friend from your list.
	else
	{
		//Erases friend at said id Location
		friends.erase(friends.begin() + index_of_id);
	}
}
int User::getId()
{
	return id;
}
string User::getName()
{
	return name;
}
int User::getBirthYear()
{
	return birth_year;
}
int User::getZip()
{
	return zip;
}
vector<int> User::getFriends()
{
	return friends;
}

void User::printFriends()
{
	//Format of the header of the table
	cout << "ID" << setw(10);
	cout << "Name" << setw(20);
	cout << "Year" << setw(6);
	cout << "Zip" << setw(15);
	cout << setfill('=') << setw(40) << endl;	
	cout << '=' << endl;
	for(int i = 0; i < friends.size();i++)
	{
		//To be used for formatting purposes later.
		string nameholder = friends[i].name;
		int strlength = nameholder.length();

		cout << setfill(' '); 
		cout << friends[i].id << "." << setw(strlength + 6);
		cout << friends[i].name << setw(24 - strlength);
		cout << friends[i].birth_year << setw(8);
		cout << friends[i].zip;
		cout << endl;
	}
}


