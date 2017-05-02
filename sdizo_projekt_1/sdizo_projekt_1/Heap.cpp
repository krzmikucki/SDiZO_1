
#include <iomanip>
#include <climits>
#include <cstring>
#include <string>
#include <fstream>
#include "Heap.h"

using namespace std;

Heap::Heap(int size) {

	heap = new int[size];
	this->size = size;
	for (int i = 0; i < size; i++)
	{
		heap[i] = INT_MIN;
	}
	currentIndex = 0;
}

void Heap::buildFromFile(string filename)
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
		new Heap(n);
		for (int i = 0; i < n; i++)
		{
			getline(file, number);
			insert(atoi(number.c_str()));
		}
	}
}


void Heap::insert(int value) {
	if (currentIndex >= size)
		resize();

	if (currentIndex < size) {
		heap[currentIndex] = value;
		int s = currentIndex;
		while (s != 0) {
			int p = s / 2;
			if (heap[p] < heap[s]) {
				std::swap(heap[p], heap[s]);
				s /= 2;
			}
			else
				break;
		}
		currentIndex++;

	}
}

void Heap::remove() {
	if (currentIndex >= 1) {
		int size = this->currentIndex - 1;
		heap[0] = heap[size];

		int tmp = 0;
		while (tmp * 2 + 1 <= size) {
			if (heap[tmp] < heap[tmp * 2 + 1] || heap[tmp] < heap[tmp * 2 + 2]) {
				if (heap[tmp * 2 + 1] > heap[tmp * 2 + 2] || tmp * 2 + 2 > size) {
					std::swap(heap[tmp], heap[(tmp * 2) + 1]);
					tmp = (tmp * 2) + 1;
				}
				else {
					std::swap(heap[tmp], heap[(tmp * 2) + 2]);
					tmp = (tmp * 2) + 2;
				}
			}
			else
				break;
		}
		currentIndex--;
		decreaseArray();
	}

}
void Heap::showHeap() {
	int levels = 0;

	int s = size;
	printf("ROZMIAR KOPCA: %d \n", size);
	while (s != 1)
	{
		s /= 2;
		levels++;
	}
	++levels;
	int counter = 0;
	printf("Liczba poziomów: %d \n", levels);
	printf("%d \n", heap[0]);
	int tmp = 1 * 2;
	for (int i = 1; i < currentIndex; i++)
	{



		printf("%d ", heap[i]);
		counter++;

		if (counter == tmp)
		{
			counter = 0;
			tmp *= 2;

			printf("\n");
		}
	}
	printf("\n");
	printf("\n");
	printf("\n");


}
void Heap::draw(string sp, string sn, int v)	//rysowanie kopca 
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;	//ustawienie wartosci stringow ktore pozwola na rysowanie lini
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	string s;

	if (v < size)
	{
		s = sp;
		if (sn == cr)
			s[s.length() - 2] = ' ';
		draw(s + cp, cr, 2 * v + 2);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << heap[v] << endl;

		s = sp;
		if (sn == cl)
			s[s.length() - 2] = ' ';
		draw(s + cp, cl, 2 * v+1);
	}
}
bool Heap::find(int v)
{
	for (int i = 1; i <= size; i++)
	{
		if (heap[i] == v)
			return true;
	}
	return false;
}

int Heap::getSize()
{
	return size;
}

void Heap::resize() {

	int *newArr = new int[++size];
	memcpy(newArr, heap, (size - 1) * sizeof(int));

	delete[] heap;
	heap = newArr;
	heap[size - 1] = 0;

}

void Heap::decreaseArray() {

	int *newArr = new int[--size];
	memcpy(newArr, heap, (size)* sizeof(int));

	delete[] heap;
	heap = newArr;


}