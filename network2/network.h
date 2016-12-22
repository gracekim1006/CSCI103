#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <vector>
//Does this give me access to the User Class?
#include "user.h"

using std::string;
using std::vector;


class Network {
 public:
  Network();
  //~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(string username, int yr, int zipcode);
  int add_connection(string name1, string name2);
  int remove_connection(string name1, string name2);
  int get_id(string username);
  void print_users();
  void printUserFriends(string username);
  User* getUser(int id);
  vector<int> shortest_path(int from, int to);
  vector<vector<int> > groups();
  vector<int> suggest_friends(int who, int &score);
  void reset();
  void group_reset();
 private:
 vector<User> list_of_users;	
 bool idlist[100];
  
};


#endif
