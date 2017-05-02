#pragma once
#include <string>
using namespace std;
class Array
{
public:

	Array();
	Array(int);
	~Array();

	void buildFromFile(string);
	void addAtEnd(int);
	void addAtBeginning(int);
	void add(unsigned int, int);
	void removeAtEnd();
	void removeAtBeginning();
	void remove(unsigned int);
	void show();
	int get(unsigned int);
	int getSize();
	bool find(int);

private:
	int size;
	int *array;
};

