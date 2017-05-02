#pragma once
#include <string>

using namespace std;
class BinaryHeap
{
public:
	int size=0;
	int *heap;
	string cr, cl, cp;
	BinaryHeap();
	BinaryHeap(int n);
	~BinaryHeap();

	void buildFromFile(string filename);
	void insert(int);
	void remove(int);
	void heapUp(int);
	void heapDown(int);
	void swap(int, int);
	int getSize();
	bool find(int);
	int left(int);
	int right(int);
	void draw(string, string, int);
	void show();
};

