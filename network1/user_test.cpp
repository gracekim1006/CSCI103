#include <iostream>
#include "user.h"
#include <string>

using namespace std; 

int main()
{
	int id = 0;
	string name = "Sandeep";
	int zip = 95070;
	int year = 1998;
	User* sandeep = new User(name, id, year, zip);
	cout << sandeep->getName() << endl;
	cout << sandeep->getId() << endl;
	cout << sandeep->getBirthYear() << endl;
	cout << sandeep->getZip() << endl;
	return 0;
}