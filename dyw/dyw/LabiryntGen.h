#pragma once
#include <vector>

using namespace std;

class LabiryntGen
{
	vector <int> graniczace;
	int *odwiedzony;
	int *graniczacy;
	int n,v;//ilosc obszarow w planszy i poziom planszy;
	int wersja;//wersja labiryntu
public:
	LabiryntGen();
	~LabiryntGen();

	void Generuj();//generuje labirynt
	void nastepnaWersja();//zmienia wersje labiryntu
};