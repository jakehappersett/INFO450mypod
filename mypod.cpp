#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

///////////////////// turn back: here be dragons ///////////////////

class node
{
	char artist[50];
	char song[50];
	node *next;
public:
	void setnode(char a[], char s[]);
	void display();
	friend class linkedList;
};
void node::setnode(char a[], char s[])
{
	strcpy_s(artist, a);
	strcpy_s(song, s);
	next = NULL;
}
void node::display()
{
	cout << "artist : " << artist << " song : " << song << endl;
}

// Linked List Class
class linkedList
{
	node *head;
	node *tail;
public:
	linkedList();
	void addNodeToEnd(node *nptr);
	void skipsong(int n);
	void playsong();
	int removeNode(char e[]);
	void whatamievendoingthismakesnosense();
};

// linkedList constructor
linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}
void linkedList::addNodeToEnd(node *ptr)
{
	// if list is empty
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}


int linkedList::removeNode(char e[])
{
	//this actually works now
	node *ptr = head;
	if (ptr == NULL)  // empty list
		return -1;


	// if node is at the head
	if (strcmp(head->song, e) == 0)
	{
		//if only 1 node in the list
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}


	while (ptr != NULL)
	{
		if (ptr->next && (strcmp((ptr->next)->song, e) == 0))
		{
			//if its at th eend
			if (tail == ptr->next)
				tail = ptr;
			//something is going on here
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}
void linkedList::skipsong(int n)
{
	//this isn't working anymore :(
	node *ptr;
	ptr = head;
	for (int i=0; i < n; i++)
	{
		ptr = ptr->next;
	}
}
void linkedList::playsong()
{
	node *ptr;
	ptr = head;
	if (ptr == NULL)
	{
		cout << "nothin' here" << endl;
		return;
	}
	else
	{
		cout << "playing " << ptr->artist << ", " << ptr->song << endl;
		cout << endl;
	}
}
void linkedList::whatamievendoingthismakesnosense()
{
	node *ptr;
	ptr = head;
	while (1 == 1)
	{
		char ans;
		//play song ---- skip song (move n down the list)----- delete song
		cout << "do what" << endl;
		cout << "[p]lay" << endl;
		cout << "[s]kip" << endl;
		cout << "[d]elete" << endl;
		cout << "[q]uit" << endl;
		cin >> ans;

		if (ans == 'p')
		{

			if (ptr == NULL)
				ptr = head;
			cout << "playing " << ptr->artist << ", " << ptr->song << endl;
			cout << endl;
			ptr = ptr->next;

		}
		else if (ans == 's')
		{

			int i = 0;
			int num;
			cout << "how many songs do you want to skip" << endl;
			cin >> num;
			//skip forward num times
			//somethings not working in this forloop
			for (i; i<num; i++)
			{
				if (ptr == NULL)
					ptr = head;
				ptr = ptr->next;
			}

		}
		else if (ans == 'd')
		{
			char e[50];
			cout << "enter the EXACT songname to be deleted " << endl;
			// i've created a monster
			cin.clear();
			cin.ignore();
			cin.getline(e, 50);
			removeNode(e);
		}
		else if (ans == 'q')
		{
			break;
		}
	}
}

int main()
{
	linkedList *mylist = new linkedList();
	//node *newnode = new node(4);
	char s[50];
	cout << "enter file path" << endl;
	cin.getline(s, 50);
	ifstream infile(s);
	if (!infile)
	{
		cout << "didn't work" << endl;
		return -1;
	}
	while (!infile.eof())
	{
		//node *p;
		char a[50];
		char s[50];

		infile.getline(a, 50, ',');
		if (strlen(a))
		{
			infile.getline(s, 50, ',');
			node *p = new node();
			p->setnode(a, s);
			//cout << "a " << a << endl;
			//cout << "s " << s << endl;
			mylist->addNodeToEnd(p);
		}
	}
	infile.close();
	mylist->whatamievendoingthismakesnosense();
	return 0;
}

