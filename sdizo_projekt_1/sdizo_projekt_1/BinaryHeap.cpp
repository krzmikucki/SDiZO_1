#include "BinaryHeap.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

// budowanie z pe³nej tablicy za pomoc¹ heapdown
using namespace std;


BinaryHeap::BinaryHeap(){
	size = 0;
	heap =new  int[0];
}


BinaryHeap::BinaryHeap(int n) {
	size = n;
	heap = new  int[n];
}


BinaryHeap::~BinaryHeap()
{
	delete[] heap;
}

void BinaryHeap::buildFromFile(string filename)
{

	string number;
	fstream file;
	file.open(filename, ios::in);
	//sprawdzenie czy plik istnieje
	if (file.good() == false)
	{
		cout << "Niepoprawna nazwa pliku";
		cin.ignore();
		exit(0);
	}
	//wczytanie kolejnych linii z liczbami
	else {
		string number;
		getline(file, number);
		int n = atoi(number.c_str());		//pierwsza linia okresla ile danych liczb jest podanych w pliku i jest pobierany do zmiennej n
		new BinaryHeap(n);
		for (int i = 0; i < n; i++)
		{
			getline(file, number);
			insert(atoi(number.c_str()));
		}
	}
}

void BinaryHeap::insert(int value) //dodaje wartosc do kopca
{
	size++;

	int * nheap = new int[size]; //zarezerwowanie miejsca na now¹ tablicê

	for (int i = 0; i < size - 1; i++) //skopiowanie zawartoœci tablicy do nowej tablicy
	{
		nheap[i] = heap[i];
	}

	heap[size - 1] = value; //dodanie wartosci na ostatnie miejsce w tablicy
	delete[] heap;	//zwolnienie pamiêci zajmowanej przez star¹ tablicê
	heap = nheap;	//ustawienie wskaznika tablicy na nowa tablice
	nheap = nullptr;//usuniecie tymczasowego wskaznika
	//wywolanie funkcji przywracajacej wlasciwosc kopca
	heapUp(size);
	
}

void BinaryHeap::heapUp(int index) //funkcja przywraca w³asnosc kopca po do daniu wartosci
{
	while (index != 0)		//wywolywanie petli do momentu dojscia na szczyt kopca
	{
		if (heap[(index -1) / 2] < heap[index])	//sprawdzenie czy zachowana jest wlasciwosc kopca
		{
			swap((index - 1) / 2, index);		//wywolanie funkcji zamieniajacej miesjcami elementy kopca
			index = (index - 1) / 2;		// przejscie na kolejny(blizej korzenia) poziom kopca
		}
		else
			break;
	}

}

void BinaryHeap::remove(int index)
{	
	size--;
	swap(index, size);
	int * nheap = new int[size]; //zarezerwowanie miejsca na now¹ tablicê


	for (int i = 0; i < size; i++) //skopiowanie zawartoœci tablicy do nowej tablicy
	{
		nheap[i] = heap[i];
	}

	delete[] heap;	//zwolnienie pamiêci zajmowanej przez star¹ tablicê
	heap = nheap;	//ustawienie wskaznika tablicy na nowa tablice
	nheap = nullptr;//usuniecie tymczasowego wskaznika
	
	heapDown(index);	//przywrocenie wlasnosci kopca w dol
}

void BinaryHeap::heapDown(int index) //przywracanie wlasnosci kopca w dol
{
	int lchild = left(index); //znalezienie lewego potomka 
	int rchild = right(index);	// znalezienie prawego potomka
	if (heap[lchild] > heap[rchild] )	//znalezienie wiekszego z potomkow
	{
		if (heap[index] < heap[lchild])
		{
			swap(index, lchild); //zamiana miejscami rodzica i potomka 
			index = lchild;
			heapDown(index);	//kolejne wywolanie fukcji przywracania wlasnosci kopca w dol
		}
	}
	else if (heap[index] < heap[rchild])
	{
		swap(index, rchild);	//zamiana miejscami rodzica i potomka
		index = rchild;
		heapDown(index);		//kolejne wywolanie funkcji przywracania wlasnosci kopca w dol
	}

}

int BinaryHeap::left(int parent) //zwraca wartosc lewego potomka wezla jezeli ten istnieje
{
	int l = 2 * parent+1;
	if (l <= size) //sprawdzenie czy istnieje lewy potomek 
		return l;	
	else
		return -1;
}

int BinaryHeap::right(int parent) //zwraca wartosc przawego potomka wezla jezeli ten istnieje
{
	int r = 2 * parent+2;
	if (r <= size)	//sprawdzenie czy istnieje prawy potomek
		return r;
	else
		return -1;
}

void BinaryHeap::swap(int x, int y) //funkcja zamienia miejscami elementy kopca o indekas x, y
{	
	int  z;
	z = heap[x];
	heap[x] = heap[y];
	heap[y] = z;
}

bool BinaryHeap::find(int value) //szuka pierwszego wystapienia wartosci 
{
	for (int i= 1; i <= size; i++)
	{
		if (heap[i] == value)
			return true;
	}
	return false;
}

int BinaryHeap::getSize()
{
	return size;
}

void BinaryHeap::show() //wypisuje kolejne wartosci z tablicy
{
	for (int i = 1; i <= size; i++)
	{
		cout << heap[i] << "    ";
	}
}

void BinaryHeap::draw(string sp, string sn, int v)	//rysowanie kopca 
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;	//ustawienie wartosci stringow ktore pozwola na rysowanie lini
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	string s;

	if (v <= size)
	{
		s = sp;
		if (sn == cr)
			s[s.length() - 2] = ' ';
		draw(s + cp, cr, 2 * v + 1);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << heap[v] << endl;

		s = sp;
		if (sn == cl)
			s[s.length() - 2] = ' ';
		draw(s + cp, cl, 2 * v );
	}
}