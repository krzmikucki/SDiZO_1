#include "List.h"
#include <stddef.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

List::List()
{
	head = NULL;
	last = NULL;
}

List::~List()
{
	Element *element = head; //element wskazuje na pocz¹tek listy
	Element *next;	
	for (int i = 0; i > size; i++) //petla przechodz¹ca przez cala listê
	{
		next = element->next;	//przypisanie kolejnego elementu w next
		delete element;			//usuniêcie aktualnego elementu
		element = next;			//zapisanie w element kolejnego elementu
	}
}

void List::buildFromFile(string filename)
{
	string number;
	fstream file;
	file.open(filename, ios::in);
	//sprawdzenie czy plik istnieje
	if (file.good() == false)
	{
		cout << "Niepoprawna nazwa pliku";
		exit(0);
	}
	//wczytanie kolejnych linii z liczbami
	else {
		string number;
		getline(file, number);
		int n = atoi(number.c_str());		//pierwsza linia okresla ile danych liczb jest podanych w pliku i jest pobierany do zmiennej n
		for (int i = 0; i < n; i++)
		{
			getline(file, number);
			addAtEnd(atoi(number.c_str()));
		}
	}
}

void List::addAtBeginning(int v)
{
	//stworzenie nowego elementu listy
	Element *element = new Element();
	//jesli w liscie znajduja sie juz elementy to nalezy ustawic wskaznik na poprzedni element, elementu ktory byl na poczatku
	if (size != 0)
	{
		Element *h = head;
		h->prev = element;
		if (size == 1)
			last = head;
	}
	else
		last = element;
	//ustawienie wartosci elementu oraz wskaznikow na poprzedni i nastepny element
	element->value = v;
	element->next = head;
	element->prev = NULL;
	//zaktualizowanie wskaznika na pierwszy element
	head = element;
	size++;
}

void List::addAtEnd(int v)
{
	//stworzenie nowego elementu listy
	Element *element = new Element();
	//jesli w liscie znajduja sie juz elementy to nalezy ustawic wskaznik na nastepny element, elementu ktory byl na koncu
	if (size != 0)
	{
		Element *l = last;
		l->next = element;
		if (size == 1)
			head = last;
	}
	else
		head = element;
	//ustawienie wartosci elementu oraz wskaznikow na poprzedni i nastepny element
	element->value = v;
	element->next = NULL;
	element->prev = last;
	//zaktualizowanie wskaznika na ostatni element
	last = element;
	size++;
}

void List::add(int index, int v)
{
	if (index == size)
	{
		addAtEnd(v);
		size++;
		return;
	}
	else if (index == 0)
	{
		addAtBeginning(v);
		size++;
		return;
	}

	Element *e = new Element;
	Element *ne = head;

	for (int i = 0; i < index; i++)
	{
		ne = ne->next;
	}
	Element *pe = ne->prev;

	e->value = v;
	e->next = ne;
	e->prev = pe;
	ne->prev = e;
	pe->next = e;
	size++;

	//delete ne;
	//delete pe;
}

void List::remove(int index)
{
	if (index == 0)
	{
		return;
	}

	else if (index == size)
	{
		removeLast();
		size--;
		return;
	}
	Element *element = &get(index);
	Element *ne = element->next;
	Element *pe = element->prev;
	pe->next = ne;
	ne->prev = pe;

	//delete element;
	size--;
}

void List::removeLast()
{
	Element element = *last;
	Element *e = element.prev;
	Element *lastElement = last;
	if (size > 1)
	{
		e->next = NULL;
	}
	last = e;
	delete lastElement;
	size--;
}

void List::removeFirst()
{
	Element element = *head;
	Element *e = element.next;
	Element *firstElement = head;
	if (size > 1)
	{
		e->prev = NULL;
	}
	head = e;
	delete firstElement;
	size--;
}

List::Element List::get(int index)
{
	//sprawdzenie czy lepiej od pocz¹tku czy od koñca
	Element element = *head;

	for (int i = 0; i < index; i++)
	{
		element = *element.next;
	}
	return element;
}

void List::show()
{
	if (size == 0)
	{
		cout << "Lista jest pusta";
		return;
	}
	Element element = *head;

	for (int i = 0; i < size; i++)
	{
		cout << "  " << element.value;
		if (element.next != NULL)
		{
			element = *element.next;

		}
	}

}

bool List::find(int value)
{
	if (size == 0)
	{
		cout << "Lista jest pusta";
		return false;
	}
	Element element = *head;
	for (int i = 0; i < size; i++)
	{
		if (element.value == value)
			return true;
		if (size > 1 && element.next !=nullptr)
		{
			element = *element.next;
		}
	}
	return false;

}

int List::getSize()
{
	return size;
}