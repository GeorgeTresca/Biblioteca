#pragma once
#include "Carte.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class CarteRepo {
	vector<Carte> all;
	/*
	metoda privata verifica daca exista deja c in repository
	*/
	bool exist(const Carte& c);
public:
	CarteRepo() = default;
	//nu permitem copierea de obiecte
	CarteRepo(const CarteRepo& ct) = delete;
	/*
	Salvare pet
	arunca exceptie daca mai exista o carte cu acelasi titlu si autor
	*/
	void store(const Carte& p);

	void modifica(const Carte& c);

	void sterge(string titlu, string autor);

	/*
	Cauta
	arunca exceptie daca nu exista carte
	*/
	const Carte& find(string titlu, string autor);

	void sterge_carte(Carte s);


	Carte modifica_carte(Carte s);

	/*
	returneaza toate cartile salvate
	*/
	const vector<Carte>& getAll() const noexcept;

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class CarteRepoException {
	string msg;
public:
	CarteRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	string getMsg()const { return msg; }
	friend ostream& operator<<(ostream& out, const CarteRepoException& ex);
};

ostream& operator<<(ostream& out, const CarteRepoException& ex);

void testeRepo();
