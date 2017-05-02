#include "Array.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
//implementacja tablicy dynamicznej

using namespace std;

Array::Array()
{
	size = 0;
	array = new int[size];
}

Array::Array(int n)
{
	//Zaalokowanie miejsca w pami�ci na tablic� o rozmiarze size
	size = n;
	array = new int[n];
}

Array::~Array() //jedn� konwencje zastosowa�
{
	//zwolnienie w pami�ci miejsca zajmowanego przez array;
	delete[] array;
}

void Array::buildFromFile(string filename)
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
		size = n;
		array = new int[n];
		for (int i = 0; i < n; i++)
		{
			getline(file, number);
			array[i] = atoi(number.c_str());
		}
	}
}

void Array::addAtEnd(int value)
{
	//dodanie elementu value na ko�cu tablicy

	size++;

	int * narray = new int[size]; //zarezerwowanie miejsca na now� tablic�

	for (int i = 0; i < size -1 ; i++) //skopiowanie zawarto�ci tablicy do nowej tablicy
	{
		narray[i] = array[i];
	}

	narray[size - 1] = value; //dodanie wartosci na ostatnie miejsce w tablicy
	delete[] array;	//zwolnienie pami�ci zajmowanej przez star� tablic�
	array = narray;	//ustawienie wskaznika tablicy na nowa tablice
	narray = nullptr;//usuniecie tymczasowego wskaznika
}

void Array::addAtBeginning(int value)
{
	
	size++;
	int * narray = new int[size]; //zarezerwowanie miejsca na now� tablic�

	narray[0] = value; //wpisanie wartosci na pierwsze miejsce w tablicy

	for (int i = 1; i < size; i++) //skopiowanie zawarto�ci tablicy do nowej tablicy
	{
		narray[i] = array[i-1];
	}

	delete[] array;	//zwolnienie pami�ci zajmowanej przez star� tablic�
	array = narray;	//ustawienie wskaznika tablicy na nowa tablice
	narray = nullptr;//usuniecie tymczasowego wskaznika
}

void Array::add(unsigned int n, int value)
{
	size++;
	int * narray = new int[size]; //zarezerwowanie miejsca na now� tablic�


	for (int i = 0; i < size; i++) //skopiowanie zawarto�ci tablicy do nowej tablicy
	{
		if (i<n)
			narray[i] = array[i];
		else if (i>n)
			narray[i] = array[i-1];
	}
	narray[n] = value; //wpisanie wartosci na n-tym miejscu w tablicy

	delete[] array;	//zwolnienie pami�ci zajmowanej przez star� tablic�
	array = narray;	//ustawienie wskaznika tablicy na nowa tablice
	narray = nullptr;//usuniecie tymczasowego wskaznika

}

void Array::removeAtEnd()
{
	//size--;
	//skr�cenie tablicy o ostatni element
	//array = (int*)realloc(array, size*sizeof(int));
	size--;
	int * narray = new int[size]; //zarezerwowanie miejsca na now� tablic�


	for (int i = 0; i < size ; i++) //skopiowanie zawarto�ci tablicy do nowej tablicy
	{
		narray[i] = array[i];
	}

	delete[] array;	//zwolnienie pami�ci zajmowanej przez star� tablic�
	array = narray;	//ustawienie wskaznika tablicy na nowa tablice
	narray = nullptr;//usuniecie tymczasowego wskaznika

}

void Array::removeAtBeginning()
{
	/*
	int *temp;
	size--;
	//zaalokowanie miejsca na mniejsz� tablic�
	temp = (int*)malloc(size*sizeof(int));
	//skopiowanie element�w tablicy 
	memcpy(temp, array + 1, size*sizeof(int));
	//zwolnienie miejsca w pami�ci zaalokowanego dla array;
	free(array);
	array = temp;
	*/
	size--;
	int * narray = new int[size]; //zarezerwowanie miejsca na now� tablic�


	for (int i = 0; i < size; i++) //skopiowanie zawarto�ci tablicy do nowej tablicy
	{
		narray[i] = array[i+1];
	}

	delete[] array;	//zwolnienie pami�ci zajmowanej przez star� tablic�
	array = narray;	//ustawienie wskaznika tablicy na nowa tablice
	narray = nullptr;//usuniecie tymczasowego wskaznika

}

void Array::remove(unsigned int n)
{
	/*
	int *temp;
	size--;
	temp = (int*)malloc(size*sizeof(int));	//zaalokowanie miejsca na mniejsz� tablic�
	memcpy(temp, array, (n )*sizeof(int));	//skopiowanie kolejnych element�w tablicy z pomini�ciem tego z indeksem n
	memcpy((temp + n), (array + n+1), (size + 1 - n )*sizeof(int));
	free(array);	//zwolnienie miejsca w pami�ci zaalokowanego dla array;
	array = temp;
	*/

	size--;
	int * narray = new int[size]; //zarezerwowanie miejsca na now� tablic�


	for (int i = 0; i < size; i++) //skopiowanie zawarto�ci tablicy do nowej tablicy
	{
		if (i<n)
			narray[i] = array[i];
		else if (i>=n)
			narray[i] = array[i + 1];
	}
	delete[] array;	//zwolnienie pami�ci zajmowanej przez star� tablic�
	array = narray;	//ustawienie wskaznika tablicy na nowa tablice
	narray = nullptr;//usuniecie tymczasowego wskaznika
	
}

bool Array::find(int value)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == value)
			return true;
	}
	return false;
}

void Array::show()
{
	for (int i = 0; i < size; i++)
	{
		cout << "  "<< get(i) ;
	}
}

int Array::getSize()
{

	return size;
}

int Array::get(unsigned int index)
{
	return array[index];
}
