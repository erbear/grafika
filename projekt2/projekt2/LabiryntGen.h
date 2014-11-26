#pragma once
#include <vector>

using namespace std;

class LabiryntGen
{
	vector <int> graniczace;
	vector <int>  polaczenia;
	int *odwiedzony;
	int *graniczacy;
	int n,v;//ilosc obszarow w planszy i poziom planszy;
	int wersja;//wersja labiryntu
public:
	LabiryntGen(int);
	~LabiryntGen();

	vector <int> Generuj();//generuje labirynt
	void nastepnaWersja();//zmienia wersje labiryntu
};