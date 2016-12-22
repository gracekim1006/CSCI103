#include <iostream>
#include <iomanip> 
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include "network.h"
 

using namespace std;

Network::Network()
{
	//Making the ID List all false because the number for the ID
	//hasn't been used yet.
	for(int i = 0; i < 100; i++)
	{
		idlist[i] = false;
	}
}
//No destructor needed
int Network::read_friends(const char *filename)
{
	int number_of_users;
	//Opening the ifstream stream
	ifstream ifile (filename);
	if(ifile.fail())
	{
		cout << "Couldn't read the file in" << endl;
		return -1;
	}	
	//Getting the number of list_of_users we are about to read in
	ifile >> number_of_users;
	if(ifile.fail())
	{
		cout << "Number of list_of_users could not be found" << endl;
		return -1;
	}
	//Reading in the list_of_users info
	for(int i = 0; i < number_of_users; i++)
	{
		//User's ID
		int idNumber;
		ifile >> idNumber;
		if(ifile.fail())
		{
			cout << "Couldn't read ID in" << endl;
			return -1;
		}	
		//This ID number has been used.
		idlist[idNumber] = true;
		//User's name
		string username;
		string myline;
		//Blank Line needs to be consumed first
		string nothing;
		getline(ifile,nothing);
		//Getting full name
		getline(ifile, myline);
		stringstream s(myline);
		string name;
		//Used for spacing purposes
		int count = 0;
		while(s >> name)
		{
			//If there is a last name to come then put a space
			//Note: Only valid when person has first/last name format 
			//So names like "Matthew Van Den Berg" would fail.
			if(count == 0)
			{
				username += name + " ";
				count++;
			}
			else
			{
				username += name;
				count++;
			}

		}
		//User's year
		int year;
		ifile >> year;
		if(ifile.fail())
		{
			cout << "Couldn't read year in" << endl;
			return -1;
		}
		//User's ZIP
		int zip;
		ifile >> zip;
		if(ifile.fail())
		{
			cout << "Couldn't read zip in" << endl;
			return -1;
		}
		//Creating the person
		User* person = new User(username, idNumber, year, zip);
		
		//Adding in his friends 
		string blank;
		string line;
		//Blank Line we have to parse through
		getline(ifile, blank);
		//Getting actual friend connections
		getline(ifile, line);
		//Going to actually get the data
		stringstream ss(line);
		int num;
		while(ss >> num)
		{
			//Getting ID Number of friends
			person->add_friend(num);
		}
		list_of_users.push_back(*person);
	}
	//Successful
	return 0;
}
int Network::write_friends(const char *filename)
{
	ofstream ofile (filename);
	ofile << list_of_users.size() << endl;
	for(int i = 0; i < list_of_users.size(); i++)
	{
		//IDNum 
		ofile << list_of_users[i].getId();

		string name = list_of_users[i].getName();
		int length = name.length();
		ofile << endl << '\t' << setw(length);

		//Name 
		ofile << list_of_users[i].getName() << endl << '\t' << setw(4);

		//Birth Year
	    ofile << list_of_users[i].getBirthYear() << endl << '\t' << setw(5);

		//Zipcode
		ofile << list_of_users[i].getZip() << endl << '\t' << setw(1);

		vector<int> list_of_friends = list_of_users[i].getFriends();
		//If no friends for the user.
		if(list_of_friends.size() == 0)
		{
			ofile << " " << endl;
		}
		for(int j = 0; j < list_of_friends.size(); j++)
		{
			if(j != list_of_friends.size() - 1)
			{
				ofile << list_of_friends[j] << " ";
			}
			else
			{
				ofile << list_of_friends[j];
				ofile << endl;
			}
		}


	}
	return 0;
}
void Network::add_user(string username, int yr, int zipcode)
{
	int idNumber = -1;
	for(int i = 0; i < 100; i++)
	{	
		//the second we find a useable ID, break
		if(idlist[i] == false)
		{
			idNumber = i;
			break;
		}
	}
	//If all there are already 100 users.
	if(idNumber == -1)
	{
		cout << "Sorry there are too many users" << endl;
		return;
	}
	else
	{
		User* person = new User(username, idNumber, yr, zipcode);
		//Id will now be in use
		idlist[idNumber] = true;
		list_of_users.push_back(*person);
		cout << "Just added " << username << "!" << endl;
	}
}
int Network::add_connection(string name1, string name2)
{
	int index_of_user1 = -1;
	int index_of_user2 = -1;

	int idnum1 = get_id(name1);
	int idnum2 = get_id(name2);
	//If either of the users are not in the system
	if(idnum1 == -1 || idnum2 == -1)
	{
		cout << "A name you entered is not in the system" << endl;
		return -1;
	}

	//Finding to see if the person1 is in the network
	for(int i = 0; i < list_of_users.size(); i++)
	{
		//If someone matches the first name given
		if(list_of_users[i].getName() == name1)
		{
			index_of_user1 = i;
			break;
		}
	}
	for(int i = 0; i < list_of_users.size(); i++)
	{
		//If someone matches the second name given
		if(list_of_users[i].getName() == name2)
		{
			index_of_user2 = i;
			break;
		}
	}
	list_of_users[index_of_user1].add_friend(idnum2);
	list_of_users[index_of_user2].add_friend(idnum1);
	return 0;
}
int Network::remove_connection(string name1, string name2)
{
	int index_of_user1 = -1;
	int index_of_user2 = -1;

	int idnum1 = get_id(name1);
	int idnum2 = get_id(name2);
	//If either of the users are not in the system
	if(idnum1 == -1 || idnum2 == -1)
	{
		cout << "A name you entered is not in the system" << endl;
		return -1;
	}

	//Finding to see if the person is in the network
	for(int i = 0; i < list_of_users.size(); i++)
	{
		//If someone matches the first name given
		if(list_of_users[i].getName() == name1)
		{
			index_of_user1 = i;
			break;
		}
	}
	for(int i = 0; i < list_of_users.size(); i++)
	{
		//If someone matches the second name given
		if(list_of_users[i].getName() == name2)
		{
			index_of_user2 = i;
			break;
		}
	}
	list_of_users[index_of_user1].delete_friend(idnum2);
	list_of_users[index_of_user2].delete_friend(idnum1);
	return 0;
}

int Network::get_id(string username)
{
	int index_of_username = -1;
	for(int i = 0; i < list_of_users.size(); i++)
	{
		if((list_of_users[i]).getName() == username)
		{
			index_of_username = i;
			break;
		}
	}
	if(index_of_username == -1)
	{
		return index_of_username;
	}
	else
	{
		return list_of_users[index_of_username].getId();		
	}
}

void Network::print_users()
{
	//If there are no users
	if(list_of_users.size() == 0)
	{
		cout << "No users in the network!" << endl;
		return;
	}
	//Format of the header of the table
	cout << "ID" << setw(10);
	cout << "Name" << setw(20);
	cout << "Year" << setw(6);
	cout << "Zip" << setw(15);
	cout << setfill('=') << setw(40) << endl;	
	cout << '=' << endl;
	for(int i = 0; i < list_of_users.size();i++)
	{
		//To be used for formatting purposes later.
		string nameholder = list_of_users[i].getName();
		int strlength = nameholder.length();

		cout << setfill(' '); 
		cout << list_of_users[i].getId() << "." << setw(strlength + 6);
		cout << list_of_users[i].getName() << setw(24 - strlength);
		cout << list_of_users[i].getBirthYear() << setw(8);
		cout << list_of_users[i].getZip();
		cout << endl;
	}
}

void Network::printUserFriends(string username)
{
	int targetIndex = -1;
	for(int i = 0; i < list_of_users.size(); i++)
	{
		if(list_of_users[i].getName() == username)
		{
			targetIndex = i;
			break;
		}
	}
	//Person is not there
	if(targetIndex == -1)
	{
		cout << username << " was not found in the network!" << endl;
		return;
	}
	//Person is there
	else
	{
		//Get Friends of person
		vector<int> friendslist = list_of_users[targetIndex].getFriends();
		//If person has no friends.
		if(friendslist.size() == 0)
		{
			cout << username << " has no friends!" << endl;
			return;
		}
		//Person has friends
		cout << "ID" << setw(10);
		cout << "Name" << setw(20);
		cout << "Year" << setw(6);
		cout << "Zip" << setw(15);
		cout << setfill('=') << setw(40) << endl;	
		cout << '=' << endl;
		//Going through each friend connection
		for(int i = 0; i < friendslist.size(); i++)
		{
			//Id number of friend
			int idnum = friendslist[i];
			//Going through the list of users to find this friend.
			for(int j = 0; j < list_of_users.size(); j++)
			{	
				//We found the User object for this Id number
				if(list_of_users[j].getId() == idnum)
				{
					//Print all info
					//To be used for formatting purposes later.
					string nameholder = list_of_users[j].getName();
					int strlength = nameholder.length();

					cout << setfill(' '); 
				   cout << list_of_users[j].getId() << "." << setw(strlength+6);
					cout << list_of_users[j].getName() << setw(24 - strlength);
					cout << list_of_users[j].getBirthYear() << setw(8);
					cout << list_of_users[j].getZip();
					cout << endl;
					break;
				}
			}
		}
	}
}
