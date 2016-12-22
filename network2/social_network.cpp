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
  	int input = 1;
  	while(input <= 9 && input > 0)
	{
		cout << "Menu options are as follows:" << endl;
		cout << "1: to add a new user!" << endl;
		cout << "2: to add a friend connection" << endl;
		cout << "3: to remove a friend connection" << endl;
		cout << "4: to print a list of users and their info" << endl;
		cout << "5: to list all friends of a user" << endl;
		cout << "6: to write all user info to a file" << endl;
		cout << "7: to find the shortest path to another user" << endl;
		cout << "8: to find the different friend groups in the network" << endl;
		cout << "9: to find suggested friends for a user" << endl;
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
		else if(input == 7)
		{
			cout << "Please enter both full names" << endl;
			//First name
			string fname1;
			string lname1;
			string username1;
			cin >> fname1;
			cin >> lname1;
			//Second name
			string fname2;
			string lname2;
			string username2;
			cin >> fname2;
			cin >> lname2;
			//Combining names
			username1 = fname1 + " " + lname1;
			username2 = fname2 + " " + lname2;
			//If names are the same
			if(username1 == username2)
			{
				cout << "Distance: 0" << endl;
				cout << username1 << endl;
			}
			//if the names aren't the same
			else
			{
				int id1 = facebook->get_id(username1);
				int id2 = facebook->get_id(username2);
				//If a user doesn't exist
				if(id1 == -1 || id2 == -1)
				{
					cout << "You're looking for a person who doesn't exist";
					cout << endl;

				}
				//If both users exist
				else
				{
					vector<int> path;
					path = facebook->shortest_path(id1, id2);
					//If there was no path found
 					if(path.size() == 0)
 					{
 						cout << "None" << endl;
 					}
 					//If there was a path found
 					else
 					{
						int distance;
						distance = path.size() - 1;
						cout << "Distance: " << distance << endl;
		
						//Actual printing of connection path;
						for(int i = 0; i < path.size(); i++)
						{
							int idnum = path[i];
		   					User* person = NULL; 
							person = facebook->getUser(idnum);
							string name = person->getName();
							if(i != path.size() - 1)
							{	
								cout << name << " -> ";
							}
							else 
							{
								cout << name << endl;
							}			
						}
					}
				}
			}
			//So we can call function again in the same run.
			facebook->reset();

		}
		else if(input == 8)
		{
			vector<vector<int> > groups;
			groups = facebook->groups();
			//Printing the sets 
			for(int i = 0; i < groups.size(); i++)
			{
				cout << "Set " << i+1 << " => ";
				for(int j = 0; j < groups[i].size(); j++)
				{
					User* person; 
					person = facebook->getUser(groups[i][j]);
					if(j != groups[i].size() - 1)
					{
						cout << person->getName() << ", ";
					}
					else 
					{
						cout << person->getName() << endl;
					}

				}
			}
			facebook->reset();
			facebook->group_reset();
		}
		else if(input == 9)
		{
			cout << "Please enter a full name" << endl;
			//Name for who
			string fname;
			string lname;
			string username;
			cin >> fname;
			cin >> lname;
			username = fname + " " + lname;

			//Getting ID for the name;
			int id = -1;
			id = facebook->get_id(username);
			if(id == -1)
			{
				cout << "User doesn't exist" << endl;
			}
			else
			{
				int num = 0;
				int& score = num;
				vector<int> suggestedFriends;
				suggestedFriends = facebook->suggest_friends(id, score);
				cout << "The suggested friend(s) is/are:" << endl;
				for(int i = 0; i < suggestedFriends.size(); i++)
				{
					int idnumOfSuggestedFriend = suggestedFriends[i];
					User* person = facebook->getUser(idnumOfSuggestedFriend);
					//Name
					cout << "  " << person->getName() << '\t';
					//Mutual Friends
					cout << "Score: " << person->score << endl;
				}

			}
			//Reset scores and checked
			facebook->reset();
		}
	}
	delete facebook;
}
