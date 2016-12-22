#include "delist.h"
#include <iostream> 

using namespace std;

//Constructs an empty Double-Ended List
DEList::DEList()
{
	head = NULL;
	tail = NULL;
}

// Destructor to clean-up memory of current list
DEList::~DEList()
{

}
// returns a Boolean 'true' if the list is empty
bool DEList::empty()
{
	if(head != NULL)
		return false;
	return true;
}
// returns number of items in the list
int DEList::size()
{
	DEItem* temp = head;
	//If empty list
	if(head == NULL)
	{
		return -1;
	}
	else
	{
		int length = 0; 
		while(temp != NULL)
		{
			temp = temp->next;
			length++;	
		}
		return length;
	}
}
// returns front item or -1 if empty list
int DEList::front()
{	
	//If empty list
	if(head == NULL)
	{
		return -1;
	}
	else
	{
		return head->val;
	}
}
// returns back item or -1 if empty list
int DEList::back()
{
	//If empty list
	if(head == NULL)
	{
		return -1;
	}
	else
	{
		return tail->val;
	}
}
// Adds a new integer to the front of the list
void DEList::push_front(int new_val)
{
	/*
	DEItem* item = new DEItem;
	item->val = new_val;
	item->prev = NULL;
	item->next = temp;
	head = item;
	*/
}
// Adds a new integer to the back of the list
void DEList::push_back(int new_val)
{

}
// Removes the front item of the list (if it exists)
void pop_front()
{

}
// Removes the back item of the list (if it exists)
void pop_back()
{

}