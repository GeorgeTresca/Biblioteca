#include "Repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void CarteRepo::store(const Carte& c)
{
	if (exist(c)) {
		throw CarteRepoException("Exista deja cartea cu titlul:" + c.getTitlu() + " scrisa de:" + c.getAutor());
	}
	all.push_back(c);
}

bool CarteRepo::exist(const Carte& c) {
	try {
		find(c.getTitlu(), c.getAutor());
		return true;
	}
	catch (CarteRepoException&) {
		return false;
	}
}
/*
Cauta
arunca exceptie daca nu exista cartea
*/

const Carte& CarteRepo::find(string titlu, string autor) {

	vector<Carte>::iterator f = std::find_if(this->all.begin(), this->all.end(),
		[=](const Carte& s) {
			return s.getTitlu() == titlu && s.getAutor() == autor;
		});

	if (f != this->all.end())
		return (*f);
	else
		throw CarteRepoException("Cartea cu titlul " + titlu + " si autorul " + autor + " nu exista in lista.\n");
}
/*const Carte& CarteRepo::find(string titlu, string autor) const {
	for (const auto& c : all) {
		if (c.getTitlu() == titlu && c.getAutor() == autor) {
			return c;
		}
	}
	//daca nu exista arunc o exceptie
	throw CarteRepoException("Nu exista cartea cu titlul:" + titlu + " scrisa de:" + autor);}*/





void CarteRepo::modifica(const Carte& c) {

	int ok = 0;
	int i = 0;
	for (const Carte& c1 : all) {
		if (c1.getTitlu() == c.getTitlu() && c1.getAutor() == c.getAutor()) {

			all[i] = c;
			ok = 1;
			break;
		}
		i++;
	}
	if (!ok)
		throw CarteRepoException("Cartea cu titlul " + c.getTitlu() + " si autorul " + c.getAutor() + " nu exista in lista");
}

void CarteRepo::sterge(string titlu, string autor) {
	int ok = 0;

	for (int i = 0; i < all.size(); i++) {
		if (all[i].getTitlu() == titlu && all[i].getAutor() == autor) {

			all.erase(all.begin() + i);
			ok = 1;
			break;
		}

	}


	if (!ok)
		throw CarteRepoException("Cartea cu titlul " + titlu + " si autorul " + autor + " nu exista in lista");
}


void CarteRepo::sterge_carte(Carte s) {
	if (!exist(s))
		throw CarteRepoException(
			"cartea cu titlul " + s.getTitlu() + " si autorul " + s.getAutor() + " nu exista in lista");
	vector<Carte> lst = getAll();
	int i = 0;
	for (auto l : lst)
	{
		if (s.getTitlu() == l.getTitlu() && s.getAutor() == l.getAutor())
		{
			all.erase(all.begin() + i);
			break;
		}
		++i;
	}
}

Carte CarteRepo::modifica_carte(Carte s) {
	if (!exist(s))
		throw CarteRepoException("cartea cu titlul " + s.getTitlu() + " si autorul " + s.getAutor() + " nu exista in lista");
	vector<Carte> lst = getAll();
	int i = 0;
	Carte aux;
	for (auto l : lst) {
		if (s.getTitlu() == l.getTitlu() && s.getAutor() == l.getAutor())
		{
			this->all[i] = s;
			aux = l;
		}
		i++;
	}

	return aux;
}

/*
returneaza toate cartile salvate
*/
const vector<Carte>& CarteRepo::getAll() const noexcept {
	return all;
}


ostream& operator<<(ostream& out, const CarteRepoException& ex) {
	out << ex.msg;
	return out;
}




void testAdauga() {
	CarteRepo rep;
	rep.store(Carte{ "a","a","a",4 });
	assert(rep.getAll().size() == 1);
	assert(rep.find("a", "a").getAutor() == "a");

	rep.store(Carte{ "b","b","b",4 });
	assert(rep.getAll().size() == 2);

	//nu pot adauga 2 cu acelasi tip si specie
	try {
		rep.store(Carte{ "a","a","x",4 });
		assert(false);
	}
	catch (const CarteRepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		rep.find("c", "c");
		assert(false);
	}
	catch (const CarteRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCauta() {
	CarteRepo rep;
	rep.store(Carte{ "a","a","a",4 });
	rep.store(Carte{ "b","b","b",4 });

	auto c = rep.find("a", "a");
	assert(c.getAutor() == "a");
	assert(c.getTitlu() == "a");

	//arunca exceptie daca nu gaseste
	try {
		rep.find("a", "b");
		assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testeRepo() {
	testAdauga();
	testCauta();
}