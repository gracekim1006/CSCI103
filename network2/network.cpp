#include <iostream>
#include <iomanip> 
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include "network.h"
#include <deque> 

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
		User person(username, idNumber, year, zip);
		
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
			person.add_friend(num);
		}
		list_of_users.push_back(person);
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

//Checks if User is here and returns pointer to it. 
//If user doesn't exists then pointer will be null
User* Network::getUser(int id)
{
	//To be assigned later
	User* ptr = NULL;
	for(int i = 0; i < list_of_users.size(); i++)
	{
		if(list_of_users[i].getId() == id)
		{
			//return pointer to User
			ptr = &(list_of_users[i]);
			break;
		}
	}
	return ptr;
}
vector<int> Network::shortest_path(int from, int to)
{
	vector<int> path;
	//Here for calls outside the call in the driver.
	if(from == to)
	{
		return path;
	}
	bool found = false;
	//Max size is all the users
	deque<int> dq;
 	
 	//Add the starting person to the queue
 	dq.push_back(from);

 	while(dq.empty() == false)
 	{
 		//Look at current id
 		int current_id = dq[0];
 		//Get user with that id;
 		User* person = NULL;
 		person = getUser(current_id);
 		//This person has been looked through
 		person->checked = true;
 		//Vector of friends id
 		vector<int> friends = person->getFriends();
 		for(int i = 0; i < friends.size(); i++)
 		{

 			//If the user is the target we are looking for
 			if(friends[i] == to)
 			{
 				User* friendOfPerson = NULL;
 				//Getting user of id
 				friendOfPerson = getUser(friends[i]);
 				//Setting predecessor
 				friendOfPerson->predecessor = current_id;
 				//Setting depth
 				friendOfPerson->depth = (person->depth + 1);
 				//Escape out of for loop to set the path up
 				//We don't need to keep checking
 				//cout << "Found the first time" << endl;
  				found = true;
 				break;
 			}
 			else
 			{
 				User* friendOfPerson = NULL;
 				friendOfPerson = getUser(friends[i]);
 				//If the person has already been added to the queue
 				//If the person has already been compared to "to"
 				if(friendOfPerson->checked == false)
 				{
 					//Setting predecessor
 					friendOfPerson->predecessor = current_id;
 					//Setting depth
 					friendOfPerson->depth = (person->depth + 1);
 					//Making sure the person has been checked
 					friendOfPerson->checked = true;
 					//Add person to the queue
 					dq.push_back(friends[i]);
 				}
 			}
 		}
 		//We need to break out of the while loop as well
 		if(found == true)
 		{
 			//cout << "Second found called" << endl;
 			break;
 		}
 		//We are done with its use now so get rid of it, and on to the next user
 		dq.pop_front();
 	}//Ending of while loop
 	if(found == true)
 	{
 		//cout << "Final found called" << endl;
 		//Target user
 		User* foo = NULL;
 		foo = getUser(to);
 		//Add target user id to the begining of the solution vector
 		path.push_back(foo->getId());
 		//While we haven't reached the base case
 		while(foo->predecessor != -1)
 		{
 			//Getting ID of predecessor
 			int pred = 0;
 			pred = foo->predecessor;
 			//Adding ID to the solution vector
 			path.insert(path.begin(), pred);

 			//Changing the person we are checking to the predecessor
 			//After this we can get its predecessor unless we are at the head
 			foo = getUser(pred);
 		
 		}
 	}
 	//Reversing the order in path
 	//cout << "Returned final path return" << endl;
 	return path;
}

//Will reset predecessor/depth/checked values
void Network::reset()
{
	for(int i = 0; i < list_of_users.size(); i++)
	{
		list_of_users[i].checked = false;
		list_of_users[i].depth = 0;
		list_of_users[i].predecessor = -1;
		list_of_users[i].score = 0;
	}
}


vector<vector<int> > Network::groups()
{
	vector<vector <int> > groups;
	//Going through all users
	for(int i = 0; i < list_of_users.size(); i++)
	{
		//Checking if a user has already been placed in a group
		if(list_of_users[i].added == false)
		{
			//Adding first person 
			vector<int> a_group; 
			int id1 = list_of_users[i].getId();
			a_group.push_back(id1);
			list_of_users[i].added = true;
			for(int j = 0; j < list_of_users.size(); j++)
			{
				int id2 = list_of_users[j].getId();

				vector<int> path = shortest_path(id1, id2);
				//Path would be empty if the id numbers are the same
				if(path.size() != 0 && id1 != id2)
				{

					a_group.push_back(id2);
					list_of_users[j].added = true;
				}
				reset();
			}
			groups.push_back(a_group);
		}
	}
	return groups;
}

//Resets added data member so user can call groups more than once.
void Network::group_reset()
{
	for(int i = 0; i < list_of_users.size(); i++)
	{
		list_of_users[i].added = false;
	}
}
vector<int> Network::suggest_friends(int who, int &score)
{
	//We need to reset everything first if we want to use this
	//Idnum of person we are looking for is who
	//Create a breadth first search 
	User* personOfInterest = getUser(who);
	//Creating a suggestFriends array to parse through later.
	vector<int> suggestedFriendsForWho;
	for(int i = 0; i < list_of_users.size(); i++)
	{
		//If we are not looking at the same person
		if(list_of_users[i].getId() != who)
		{
			//Shortest path between who and a user
			vector<int> path = shortest_path(who, list_of_users[i].getId());
			//Depth is this.
			int depth = list_of_users[i].depth;
			//int depth = path.size() - 1;
			if(depth == 2)
			{
				suggestedFriendsForWho.push_back(list_of_users[i].getId());
			}
		}
		//We have to reset the checked and depths for people after we call 
		//shortest path.
		reset();
	}	


	vector<int> friendsOfWho = personOfInterest->getFriends();
	//Compare friends of people added to the list and people of depth 2
	for(int i = 0; i < friendsOfWho.size(); i++)
	{
		//Check if each friend is friends with the person here.
		for(int j = 0; j < suggestedFriendsForWho.size(); j++)
		{
			//Get the user for the Id in suggestedFriendsForWho
			User* other = getUser(suggestedFriendsForWho[j]);
			//Get friends of person we are comparing.
			vector<int> friendsOfOther = other->getFriends();
			for(int k = 0; k < friendsOfOther.size();k++)
			{
				//If a friend of the other is a friend of the who
				//increase that person's score
				if(friendsOfOther[k] == friendsOfWho[i])
				{
					other->score += 1;
				}
			}
		}
	}


	//Setting the score to a min
	score = 0;
	//Getting people with the highest score 
	for(int i = 0; i < suggestedFriendsForWho.size(); i++)
	{
		User* person;
		person = getUser(suggestedFriendsForWho[i]);
		//If person has a higher score than the highest score.
		if(person->score > score)
		{
			score = person->score;
		}
	}
	//Removing people who don't have the max score
	//Because index changes as we remove people this is necessary
	int counter = 0;
	while(counter != suggestedFriendsForWho.size())
	{
		int idnum = suggestedFriendsForWho[counter];
		User* person;
		person = getUser(idnum);
		//Assuming the other part is right and score is the max score
		if(person->score == score)
		{
			counter++;
		}
		else
		{
		suggestedFriendsForWho.erase(suggestedFriendsForWho.begin() + counter);
		}
	}
	return suggestedFriendsForWho;

}
/*
void Network::delete_all_users()
{
	while(list_of_users.size() != 0)
	{
		delete &list_of_users[0];
		list_of_users.erase(list_of_users.begin());
	}
}
*/
