#include "LabiryntGen.h"
#include <iostream>

using namespace std;

LabiryntGen::LabiryntGen()
{
	odwiedzony = 0;
	graniczacy = 0;
	wersja=1;
}


LabiryntGen::~LabiryntGen(void)
{
	delete[] odwiedzony;
	odwiedzony = 0;
	delete[] graniczacy;
	graniczacy = 0;
}

void LabiryntGen::Generuj()
{
	cout<<"cos"<<endl;
	int z,x,y;//zmienne pomocnicze
	//wersja losowania
	srand(wersja);

	for (int i =0;i<n;i++)
	{
		//jezeli losuje pierwszy wierzcholek
		if (i ==0)
		{
			//losuje ze wszystkich wierzcholkow
			z = rand() % n;
			odwiedzony[z]=1;//dodaje do odwiedzonego 
			graniczacy[z]=1;//dodaje do graniczacego
		}
		else 
		//jezeli jest to inny wierzcholek
		{
			//losuje jeden z wierzcholkow graniczacych
			y = rand() % graniczace.size();
			z=graniczace[y];
			//i oznaczam go jako odwiedzonego
			odwiedzony[graniczace[y]] = 1;
			//natomiast przestaje on byc graniczacym
			graniczace.erase(graniczace.begin() + (y));
		}
		//tworze vector z wierzcholkami sasiadujacymi
		vector <int> dopolaczenia;
		//jezeli pozycja wierzcholka jest wieksza od 1
		//czyli nie jest to pierwszy wierzcholek
		if (z > 1 ){
			//jezeli reszta z dzielenia pozycji wierzcholka jest rozna od jeden
			//czyli czy wierzcholek nie znajduje sie przy lewej krawedzi
			if ((z%v)!=1)
			{
				//jezeli wierzcholek po lewej nie byl graniczacy
				//to dodaje go do graniczacych
				if (graniczacy[z-1]==0)
				{
					
					graniczace.push_back(z-1);
					graniczacy[z-1] = 1;

				}
				//jesli jednak byl w graniczacych to sprawdzam czy byl odwiedzony
				//jesli tak to dodaje go do wierzcholkow ktore beda losowane do polaczenia sie z nimi
				else if (odwiedzony[z-1]==1)
						dopolaczenia.push_back(z-1);
			}
			//jezeli pozycja wierzcholka jest wieksza od liczby wierzcholkow w wierszu
			if (z>v) {
				//jezeli wierzcholek na gorze nie byl graniczacy
				//to dodaje go do graniczacych
				if (graniczacy[z-v]==0)
				{
					graniczace.push_back(z-v);
					graniczacy[z-v] = 1;
				}//jesli jednak byl w graniczacych to sprawdzam czy byl odwiedzony
				//jesli tak to dodaje go do wierzcholkow ktore beda losowane do polaczenia sie z nimi
				else if (odwiedzony[z-v]==1)
					dopolaczenia.push_back(z-v);
			}
		}
		//jezeli pozycja wierzcholka + 1 nie jest ostatnim wierzcholkiem
		//czyli jest to przedostatni albo wczesniejszy wierzcholek
		if (z+1 <= n){
			//jesli reszta z dzielenia przez liczbe wierzcholkow w wierszu jest rozna od zera
			//czyli czy wierzcholek nie znajduje sie przy prawej scianie
			if (z%v!=0)
			{
				//jesli wierzcholek po prawej nie byl odwiedzony
				//to dodaje go do odwiedzonych
				if (graniczacy[z+1]==0)
				{
					graniczace.push_back(z+1);
					graniczacy[z+1] = 1;
				} 
				//w innym wypadku sprawdzam czy byl odwiedzony
				//jesli tak to dodanie go do wierzcholkow ktore beda losowane do polaczenia sie z nimi
				else if (odwiedzony[z+1]==1)
						dopolaczenia.push_back(z+1);
			}
			//jezeli pozycja wierzcholka + liczba wierzcholkow w wierszu jest mniejsza od wszystkich wierzcholkow
			//czyli czy wierzcholek nie znajduje sie w ostatnim wierszu
			if (z+v <= n){
				//jesli wierzcholek na dole nie jest oznaczony jako graniczacy
				//to go oznaczam jako graniczacy
				if (graniczacy[z+v]==0)
				{
					graniczace.push_back(z+v);
					graniczacy[z+v] = 1;
				} 
				//w innym wypadku sprawdzam czy byl odwiedzony
				//jesli tak to dodanie go do wierzcholkow ktore beda losowane do polaczenia sie z nimi
				else if (odwiedzony[z+v]==1)
						dopolaczenia.push_back(z+v);
			}
		}
		//jezeli istnieja jakies wierzcholki z ktorymi mozna sie polaczyc
		if (dopolaczenia.size()!=0)
		{
			//to losuje jeden z nich i ustalam przejscie pomiedzy obszarami
			x = rand() % dopolaczenia.size();
			//plansza->ustalPrzejscie(dopolaczenia[x], z);
		}
		


	}
}
void LabiryntGen::nastepnaWersja()
{
	wersja++;
}