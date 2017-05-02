#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stack>
#include "Array.h"
#include "List.h"
#include "Heap.h"
#include "Generator.h"
using namespace std;


int quantity;  //przechowuje iloœæ która bêdize podawana z pliku
fstream file;
string filename = "dataList.txt";
string filenameTest = "TestDatalist.txt";
stack<int> s;
LARGE_INTEGER start, finish, clockFrequency, delta;
double tm;
double tadding[10], tremove[10], tfind[10]; //przechowuja czasy kolejnych testów
int n[] = {1000, 2000, 5000, 10000, 20000 }; // iloœæ danych do kolejnych testów

Array myArray;
List myList;
Heap heap(0);
Generator g;

int menu(const char* lista[], int ilosc_opcji, int& nr_opcji);
void wait();
void startTimer();
double endTimer();
void tests(int n);
void openFile(int);
void closeFile();
void results(string);

int a = 1, b = 1, c = 1, d = 1, u = 1;
char decyzja;
const char *opcje[] = { "MENU strzalki gora dol do poruszania kursorem ENTER - zatwierdz","Tablica","Lista","Kopiec","Testy","Zakoncz" };
const char *polecenia[] = { "Opcjestrzalki gora dol do poruszania kursorem ENTER - zatwierdz","Zbuduj z Pliku", "Usun", "Dodaj", "Znajdz", "Wyswietl", "Powrot" };
const char *dodawanie[] = { "Opcjestrzalki gora dol do poruszania kursorem ENTER - zatwierdz","Na poczatku", "Na koncu", "W srodku","Powrot" };
const char *usuwanie[] = {"Opcjestrzalki gora dol do poruszania kursorem ENTER - zatwierdz", "Z poczatku", "Z konca", "Ze srodka" ,"Powrot"};


int main() //zaimplementowanie funkcji menu dla 
{
	while (a != 5 && a != -1)
	{

		a = menu(opcje, 6, a);
		switch (a)
		{
		case 1: //Tablica
			b = 1;
			while (b != 6)
			{
				b = menu(polecenia, 7, b);
				switch (b)
				{
					srand(time(NULL));
					int n, v;
				case 1:	//budowanie z pliku
					myArray.buildFromFile(filename);
					break;
				case 2:	//usuwanie
					u = 1;
					if (myArray.getSize() == 0)
					{
						cout << "Nalezy najpierw dodac elementy do tablicy";
						wait();
						break;
					}
					while (u != 4)
					{
						u = menu(usuwanie, 5, u);
						switch (u)
						{
						case 1: //usuwanie z poczatku tablicy
							if (myArray.getSize() == 0)
							{
								cout << "Tablica jest juz pusta";
								wait();
								break;
							}
							myArray.show();
							cout << endl;
							myArray.removeAtBeginning();
							myArray.show();
							wait();
							break;
						case 2: //usuwanie z konca tablicy
							if (myArray.getSize() == 0)
							{
								cout << "Tablica jest juz pusta";
								wait();
								break;
							}
							myArray.show();
							cout << endl;
							myArray.removeAtEnd();
							myArray.show();
							wait();
							break;
						case 3: //usuwanie z losowego miejsca w tablicy
							if (myArray.getSize() == 0)
							{
								cout << "Tablica jest juz pusta";
								wait();
								break;
							}
							//n = rand() % myArray.getSize();
							cout << "Podaj indeks do usuniecia: ";
							cin >> n;
							if (n >= myArray.getSize())
								cout << "Niepoprawny indeks";
							else
							{
								myArray.show();
								myArray.remove(n);
								cout << endl << "  Usunieto element o indeksie: " << n << endl;
								myArray.show();
							}
							cin.ignore();
							wait();
							break;
						case 4:
							break;
						}
					}
					break;
				case 3:	//dodawanie
					d = 1;
					while (d != 4)
					{
						d = menu(dodawanie, 5, d);
						switch (d)
						{
						case 1:	//dodawanie na pocz¹tku
							v = rand() % 100;
							myArray.show();
							cout << endl;
							myArray.addAtBeginning(v);
							myArray.show();
							wait();
							break;
						case 2: //dodawanie na koñcu
							v = rand() % 100;
							myArray.show();
							cout << endl;
							myArray.addAtEnd(v);
							myArray.show();
							wait();
							break;
						case 3: //dodawanie w srodku
							v = rand() % 100;
							if (myArray.getSize() == 0)
							{
								myArray.addAtEnd(v);
								myArray.show();
								wait();
								break;
							}
							//n = rand() % myArray.getSize();
							cout << "Podaj indeks w ktorym chcesz dodac: ";
							cin >> n;
							if (n >= myArray.getSize())
								cout << "Niepoprawny indeks";
							else
							{
								myArray.show();
								cout << endl << "Dodano liczbe: " << v << " na miejscu: " << n << endl;
								myArray.add(n, v);
								myArray.show();
							}
							cin.ignore();
							wait();
							break;
						case 4:
							break;
						}
					}
					break;
				case 4:	//szukanie
					myArray.show();
					cout << "Podaj liczbê do wyszukania: ";
					cin >> n;
					if (myArray.find(n))
						cout << "  liczba " << n << " wystepuje w tablicy" << endl;
					else
						cout << "  liczba " << n << " nie wystepuje w tablicy" << endl;
					myArray.show();
					cin.ignore();
					wait();
					break;
				case 5:	//wyswietlanie
					myArray.show();
					wait();
					break;
				case 6:
					break;
				}
			}
			break;
		case 2:	//Lista
			b = 1;
			while (b != 6)
			{
				b = menu(polecenia, 7, b);
				switch (b)
				{
					srand(time(NULL));
					int n, v;
				case 1:	//budowanie z pliku
					myList.buildFromFile(filename);
					break;
				case 2:	//usuwanie
					if (myList.getSize() == 0)
					{
						cout << "Nalezy najpierw dodac elementy do listy";
						wait();
						break;
					}
					u = menu(usuwanie, 5, u);
					switch (u)
					{
					case 1: //usuwanie z pocz¹tku listy
						if (myList.getSize() == 0)
						{
							cout << "Lista jest juz pusta";
							wait();
							break;
						}
						myList.show();
						cout << endl;
						myList.removeFirst();
						myList.show();
						wait();
						break;
					case 2: //usuwanie z koñca listy
						if (myList.getSize() == 0)
						{
							cout << "Lista jest juz pusta";
							wait();
							break;
						}
						myList.show();
						cout << endl;
						myList.removeLast();
						myList.show();
						wait();
						break;
					case 3: //usuwanie losowego elementu
						if (myList.getSize() == 0)
						{
							cout << "Lista jest juz pusta";
							wait();
							break;
						}
						//n = rand() % myList.getSize();
						cout << "Podaj indeks do usuniecia: ";
						cin >> n;
						if (n >= myList.getSize())
							cout << "Niepoprawny indeks";
						else
						{
							myList.show();
							myList.remove(n);
							cout << endl << "  Usunieto element o indeksie: " << n << endl;
							myList.show();
						}
						cin.ignore();
						wait();
						break;
					case 4:
						break;
					} 
					break;
				case 3:	//dodawanie
					d = menu(dodawanie, 5, d);
					switch (d)
					{
					case 1:
						v = rand() % 100;
						myList.show();
						cout << endl;
						myList.addAtBeginning(v);
						myList.show();
						wait();
						break;
					case 2:
						v = rand() % 100;
						myList.show();
						cout << endl;
						myList.addAtEnd(v);
						myList.show();
						wait();
						break;
					case 3:
						v = rand() % 100;
						if (myList.getSize() <= 1)
						{
							myList.addAtEnd(v);
							myList.show();
							wait();
							break;
						}
						//n = rand() % myList.getSize();
						cout <<" Podaj indeks na ktorym chcesz dodac element: ";
						cin >> n;
						if (n >= myList.getSize())
							cout << "Niepoprawny indeks";
						else
						{
							myList.show();
							cout << endl << "Dodano liczbe: " << v << " na miejscu: " << n << endl;
							myList.add(n, v);
							myList.show();
						}
						cin.ignore();
						wait();
						break;
					case 4:
						break;
					}
					break;
				case 4:	//szukanie
					if (myList.getSize() == 0)
					{
						cout << "Nalezy najpierw dodac elementy do listy";
						wait();
						break;
					}
					myList.show();
					cout << "Podaj liczbê do wyszukania: ";
					cin >> n;
					if (myList.find(n))
						cout << "  liczba " << n << " wystepuje w tablicy" << endl;
					else
						cout << "  liczba " << n << " nie wystepuje w tablicy" << endl;
					myList.show();
					cin.ignore();
					wait();
					break;
				case 5:	//wyswietlanie
					myList.show();
					wait();
					break;
				case 6:	//wyjscie
					break;
				}
			}
			break;
		case 3:	//Kopiec
			b = 1;
			while (b != 6)
			{
				b = menu(polecenia, 7, b);
				switch (b)
				{
					srand(time(NULL));
					int n, v;
				case 1:	//budowanie z pliku
					heap.buildFromFile(filename);
					break;
				case 2:	//usuwanie
					if (heap.getSize() == 0)
					{
						cout << "Nalezy najpierw dodac elementy do kopca";
						wait();
						break;
					}
					//heap.showHeap();
					heap.draw("", "", 0);
					heap.remove();
					//heap.showHeap();
					heap.draw("", "", 0);
					wait();
					break;
				case 3:	//dodawanie
					n = rand() % 100;
					//heap.showHeap();
					heap.draw("", "", 0);
					heap.insert(n);
					cout << "dodano warotsc " << n << endl;
					//heap.showHeap();
					heap.draw("", "", 0);
					wait();
					break;
				case 4:	//szukanie
					if (heap.getSize() == 0)
					{
						cout << "Nalezy najpierw dodac elementy do kopca";
						wait();
						break;
					}
					cout << "Podaj wyszukiwana wartosc: ";
					cin >> n;
					
					if (heap.find(n))
						cout << "  liczba " << n << " wystepuje w kopcu" << endl;
					else
						cout << "  liczba " << n << " nie wystepuje w kopcu" << endl;
					heap.draw("", "", 1);
					cin.ignore();
					wait();
					break;
					
				case 5:	//wyswietlanie
					//heap.showHeap();
					heap.draw("", "", 0);
					wait();
					break;
				case 6:	//wyjscie
					break;
				}
			}
			break;
		case 4: //Testy
			for (int i = 0; i < 5; i++)
			{
				g.generate(n[i], "TestDataList.txt");
				openFile(n[i]);
				cout << "LICZBA ELEMENTOW: " << n[i]<<endl;
				tests(n[i]);
				closeFile();
			}
			wait();
			break;
		case 5://Koniec
			break;
		}
	}
	return 0;
}//

int menu(const char* lista[], int ilosc_opcji, int& nr_opcji) //funkcja do wyœwietlania menu
{

	while (1)
	{
		system("cls");
		for (int i = 0; i < ilosc_opcji; i++)
		{
			if (i == nr_opcji)
				cout << "=>";
			else
				cout << "  ";

			cout << lista[i] << endl;
		}
		fflush(stdin);
		int kl = _getch();
		if (kl == 224)
			kl = _getch();
		switch (kl)
		{
		case 80:
			if (nr_opcji < ilosc_opcji - 1)
				nr_opcji++;
			else
				nr_opcji = 1;
			break;
		case 72:
			if (nr_opcji > 1)
				nr_opcji--;
			else
				nr_opcji = ilosc_opcji - 1;
			break;
		case 13:
			system("cls");
			return nr_opcji;
		case 27:
			system("cls");
			return -1;
		}
	}
}

void wait() //wszystrzymuje prace programu
{
	fflush(stdin);
	cout << "\n\nWcisnij enter aby przejsc do menu";
	cin.get();
}

void startTimer() // zczytuje aktualny czas podczas testów
{
	QueryPerformanceFrequency(&clockFrequency);
	QueryPerformanceCounter(&start);
}

double endTimer() // zczytuje aktualny czas i ustala ile czasu minê³o od wywo³ania funkcji startTimer
{
	QueryPerformanceCounter(&finish);
	delta.QuadPart = finish.QuadPart - start.QuadPart;
	return ((double)delta.QuadPart) / clockFrequency.QuadPart;
}

void tests(int n) // Wykonuje kolejne testy dla poszczególnych struktur
{

	int index, v;

	//Tablica
	for (int i = 0; i < 10; i++)					//Dowadanie na koniec tablicy
	{
		startTimer();
		for (int j = 0; j < n; j++)
		{
			v = rand();
			myArray.addAtEnd(v);
		}
		tadding[i] = endTimer();

		startTimer();
		for (int j = 0; j < n; j++)
		{
			v = rand();
			myArray.find(v);
		}
		tfind[i] = endTimer();

		startTimer();
		for (int j = 0; j < n; j++)
		{
			myArray.removeAtEnd();
		}
		tremove[i] = endTimer();
		cout << "Koniec tablicy" << i << endl;
	}
	results("Koniec tablicy");
	for (int i = 0; i < 10; i++)						//Dodawanie na poczatek tablicy
	{
		startTimer();
		for (int j = 0; j < n; j++)
		{
			v = rand();
			myArray.addAtBeginning(v);
		}
		tadding[i] = endTimer();

		startTimer();
		for (int j = 0; j < n; j++)
		{
			myArray.removeAtBeginning();
		}
		tremove[i] = endTimer();
		cout << "Poczatek Tablicy " << i << endl;
	}
	results("Poczatek tablicy");
	for (int i = 0; i < 10; i++)						//Dodawanie w œrodek tabeli
	{
		startTimer();

		for (int j = 0; j < n; j++)
		{
			v = rand();
			if (myArray.getSize() == 0)
			{
				myArray.addAtEnd(v);
				break;
			}
			else
			{
				index = rand() % myArray.getSize();
				myArray.add(index, v);
			}
		}

		tadding[i] = endTimer();
		startTimer();
		for (int j = 0; j < n; j++)
		{
			if (myArray.getSize() == 0)
			{
				break;
			}
			else
			{
				index = rand() % myArray.getSize();
				myArray.remove(index);
			}
		}
		tremove[i] = endTimer();
		cout << "Srodek tablicy " << i << endl;
	}
	results("Srodek tablicy");

	//Lista
	for (int i = 0; i < 10; i++)					//Dowadanie na koniec tablicy
	{
		startTimer();
		for (int j = 0; j < n; j++)
		{
			v = rand();
			myList.addAtEnd(v);
		}
		tadding[i] = endTimer();

		startTimer();
		for (int j = 0; j < n; j++)
		{
			v = rand();
			myList.find(v);
		}
		tfind[i] = endTimer();


		startTimer();
		for (int j = 0; j < n; j++)
		{
			myList.removeLast();
		}
		tremove[i] = endTimer();
		cout << "Koniec listy: " << i << endl;
	}
	results("Koniec Listy");
	for (int i = 0; i < 10; i++)						//Dodawanie na poczatek tablicy
	{
		startTimer();
		for (int j = 0; j < n; j++)
		{
			v = rand();
			myList.addAtBeginning(v);
		}
		tadding[i] = endTimer();

		startTimer();
		for (int j = 0; j < n; j++)
		{
			myList.removeFirst();
		}
		tremove[i] = endTimer();
		cout << "Poczatek listy " << i << endl;
	}
	results("Poczatek listy");
	/*
	for (int i = 0; i < 10; i++)						//Dodawanie w œrodek tabeli
	{
		startTimer();

		for (int j = 0; j < n; j++)
		{
			v = rand();
			if (myList.getSize() == 0)
			{
				myList.addAtEnd(v);
				break;
			}
			else
			{
				index = rand() % myList.getSize();
				myList.add(index, v);
			}

		tadding[i] = endTimer();
		startTimer();
		for (int j = 0; j < n; j++)
		{
			if (myList.getSize() == 0)
			{
				break;
			}
			else
			{
				index = rand() % myList.getSize();
				myList.remove(index);
			}
		}
		tremove[i] = endTimer();
		cout << "Srodek listy " << i << endl;
	}
	results("Srodek listy");
	*/
	//Kopiec
	for (int i = 0; i < 10; i++)					//Kopiec
	{
		startTimer();
		for (int j = 0; j < n; j++)
		{
			v = rand();
			heap.insert(v);
		}
		tadding[i] = endTimer();

		startTimer();
		for (int j = 0; j < n; j++)
		{
			v = rand();
			heap.find(v);
		}
		tfind[i] = endTimer();

		startTimer();
		for (int j = 0; j < n; j++)
		{
			heap.remove();
		}
		tremove[i] = endTimer();
		cout << "Kopiec: " << i << endl;
	}
	results("Kopiec");

	
}
void openFile(int i) //otiwer plik w którym zapisywane bêd¹ wyniki pomiarów
{
	std::string str = std::to_string(i);
	string s = "Wyniki" + str +".txt";
	file.open(s, ios::out);
	if (file.good() == false)
	{
		cout << "File not exist";
		exit(0);
	}

}

void closeFile() //zamyka plik po dokonaniu pomiarów
{
	file.close();
}

void results(string s) // zapisuje wyniki do otwartego pliku
{
	file << s << endl;
	file << "czasy dodawania:" << endl;
	for (int i = 0; i < 10; i++)
	{
		file << tadding[i] << endl;
	}
	file << "czasy usuwania:" << endl;
	for (int i = 0; i < 10; i++)
	{
		file << tremove[i] << endl;
	}
	file << "czasy szukania:" << endl;
	for (int i = 0; i < 10; i++)
	{
		file << tfind[i] << endl;
	}


}