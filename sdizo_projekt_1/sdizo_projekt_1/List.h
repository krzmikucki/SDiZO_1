#pragma once
#include <stddef.h>
#include <string>
using namespace std;
class List
{
	
struct Element
	{
		int value;
		Element *next = NULL;
		Element *prev = NULL;
	};
public:
	Element *head;
	Element *last;
	int size=0;

	List();
	~List();
	void buildFromFile(string filename);
	void addAtBeginning(int v);
	void addAtEnd(int v);
	void add(int index, int v);
	void removeLast();
	void removeFirst();
	void remove(int index);
	void show();
	Element get(int index);
	int getSize();
	bool find(int value);
	

};

