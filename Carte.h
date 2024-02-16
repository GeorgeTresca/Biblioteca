#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Carte {
	std::string titlu;
	std::string autor;
	std::string gen;
	int an_ap;
public:
	Carte() = default;
	Carte(const string t, const string a, const string g, int p) :titlu{ t }, autor{ a }, gen{ g }, an_ap{ p } {}

	Carte(const Carte& ct) :titlu{ ct.titlu }, autor{ ct.autor }, gen{ ct.gen }, an_ap{ ct.an_ap } {
		//cout << "!!!!!!!!!!!!!!!!!!!!\n";
	}


	string getTitlu() const {
		return titlu;
	}
	string getAutor() const {
		return autor;
	}

	string getGen() const {
		return gen;
	}

	int getAn() const noexcept {
		return an_ap;
	}
	void setTitlu(string titluNou);
	void setAutor(string autorNou);
	void setGen(string genNou);
	void setAn(int anNou);
};

/*
Compara dupa titlu
returneaza true daca c1.titlu e mai mic decat c2.titlu
*/
bool cmpTitlu(const Carte& c1, const Carte& c2);

/*
Compara dupa autor
returneaza true daca c1.autor e mai mic decat c2.autor
*/
bool cmpAutor(const Carte& c1, const Carte& c2);

/*
Compara dupa gen
returneaza true daca c1.gen e mai mic decat c2.gen
*/
bool cmpGen(const Carte& c1, const Carte& c2);

void testeDomain();
