#pragma once
#include <stddef.h>
#include <string>
#include <iostream>

using namespace std;
#ifndef SDIZ_PROJEKT_1_BINARYHEAP_H
#define SDIZ_PROJEKT_1_BINARYHEAP_H


class Heap
{
public:

	int size;
	int *heap;
	string cr, cl, cp;

	int currentIndex;
	Heap(int size);
	void buildFromFile(string filename);
	void insert(int value);
	void remove();
	void showHeap();
	void draw(string, string, int);
	bool find(int v);
	int getSize();
	void resize();

	void decreaseArray();
};

#endif //SDIZ_PROJEKT_1_BINARYHEAP_H