#ifndef USER_H
#define USER_H
#include <string>
#include <vector>

using std::string;
using std::vector;

class User {
 public:
 	User(string name, int idnum, int birth_year, int zipcode);
 	//If the user exists, add him to your friend vector list.
 	void add_friend(int idnum);
 	void delete_friend(int idnumber);
 	int getId();
 	string getName();
 	int getBirthYear();
 	int getZip();
 	void printFriends();
 	vector<int> getFriends();
 	//Requires Network
 	//User* getUser(int id);
 	int depth; 
 	int predecessor;

 private:
 	int id;
 	string name;
 	int birth_year;
 	int zip;
 	vector<int> friends;
};


#endif
