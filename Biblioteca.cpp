#include "Biblioteca.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <fstream>

using namespace std;

vector<Carte> Biblioteca::generalSort(bool(*maiMicF)(const Carte&, const Carte&)) {
	vector<Carte> v{ rep.getAll() };//fac o copie	
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				//interschimbam
				Carte aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

/*
Adauga o noua carte
arunca exceptie daca: nu se poate salva, nu este valid
*/
void Biblioteca::addCarte(const string& titilu, const string& autor, const string& gen, int an) {
	Carte c{ titilu,autor,gen,an };
	val.validate(c);
	Undo.push_back(new UndoAdauga{ rep, c });
	rep.store(c);
}


Carte Biblioteca::find(const string& titlu, const string& autor) {
	return rep.find(titlu, autor);
}

void Biblioteca::modificaCarte(string titlu, string autor, string noulGen, int noulAn) {
	Carte c1{ titlu, autor, noulGen, noulAn };
	val.validate(c1);
	rep.modifica(c1);

}

void Biblioteca::stergeCarte(string titlu, string autor) {
	rep.sterge(titlu, autor);


}
/*
Sorteaza dupa titlu
*/
vector<Carte> Biblioteca::sortByTitlu() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), cmpTitlu);
	return copyAll;
	//return generalSort(cmpType);
}

/*
Sorteaza dupa autor
*/
vector<Carte> Biblioteca::sortByAutor() {
	return generalSort(cmpAutor);
}


/*
Sorteaza dupa gen+an
*/
vector<Carte> Biblioteca::sortByGenAn() {
	return generalSort([](const Carte& c1, const Carte& c2) {
		if (c1.getGen() == c2.getGen()) {
			return c1.getAn() < c2.getAn();
		}
		return c1.getGen() < c2.getGen();
		});
}

vector<Carte> Biblioteca::filtreaza(function<bool(const Carte&)> fct) {
	vector<Carte> rez;
	for (const auto& carte : rep.getAll()) {
		if (fct(carte)) {
			rez.push_back(carte);
		}
	}
	return rez;
}

vector<Carte> Biblioteca::filtrareAnMaiMic(int an) {
	/*return filtreaza([an](const Carte& c) {
		return c.getAn() < an;
		});*/
	const vector<Carte>& allCarti = getAll();
	vector<Carte> filteredCarti;
	std::copy_if(allCarti.begin(), allCarti.end(), back_inserter(filteredCarti),
		[an](const Carte& m) {
			return m.getAn() < an;
		});

	return filteredCarti;
}

vector<Carte> Biblioteca::filtrareAni(int anMin, int anMax) {
	/*return filtreaza([=](const Carte& c) {
		return c.getAn() >= anMin && c.getAn() <= anMax;
		});*/
	const vector<Carte>& allCarti = getAll();
	vector<Carte> filteredCarti;
	std::copy_if(allCarti.begin(), allCarti.end(), back_inserter(filteredCarti),
		[=](const Carte& m) {
			return m.getAn() >= anMin && m.getAn() <= anMax;
		});

	return filteredCarti;
}

vector<Carte> Biblioteca::filtrareAutor(const string& autor) {
	/*return filtreaza([autor](const Carte& c) {
		return c.getAutor() == autor;
		});*/
	const vector<Carte>& allCarti = getAll();
	vector<Carte> filteredCarti;
	std::copy_if(allCarti.begin(), allCarti.end(), back_inserter(filteredCarti),
		[autor](const Carte& m) {
			return m.getAutor() == autor;
		});

	return filteredCarti;
}

void Biblioteca::deleteCarte(string titlu, string autor, string gen, int an) {
	Carte s1{ titlu, autor, gen, an };
	val.validate(s1);
	UndoSterge* action = new UndoSterge{ rep, s1 };
	Undo.push_back(action);
	rep.sterge_carte(s1);

}

void Biblioteca::modificaCarte1(string titlu, string artist, string gen, int an) {
	Carte s1{ titlu, artist, gen, an };
	val.validate(s1);
	Carte aux = rep.modifica_carte(s1);
	UndoModifica* action = new UndoModifica{ rep, aux };
	Undo.push_back(action);

}

void Biblioteca::doUndo() {
	try {
		if (Undo.size() == 0)
			throw std::exception();
	}
	catch (std::exception) {
		throw std::exception();
	}
	try{UndoActions* act = Undo.back();
	act->DoUndo();
	Undo.pop_back();
	//delete act;}
	}
	catch (std::exception& ex) {
		throw ex;
	}
}


Carte Biblioteca::findCos(string titlu, string autor) {
	int ok = 0;
	for (auto& carte : currentCos.getAllCartiCos()) {
		if (carte.getTitlu() == titlu && carte.getAutor() == autor) {
			ok = 1;
			return carte;
		}
	}
	if (ok == 0) {
		throw CarteRepoException("Cartea nu exista in cos!");
	}
	
}

void Biblioteca::addToCos(string titlu, string autor) {

	const auto& carte = rep.find(titlu, autor);
	currentCos.addCarteinCos(carte);

}
int Biblioteca::addRandomToCos(int howMany) {
	currentCos.addRandomCarti(this->getAll(), howMany);
	return static_cast<int>(currentCos.getAllCartiCos().size());
}
void Biblioteca::emptyCos() {
	currentCos.emptyCos();
}

void Biblioteca::Export_Cos(string& fisier, int& option) {

	if (option == 1)
		fisier += ".cvs";
	else
		fisier += ".html";


	ofstream fout(fisier);

	for (auto item : getCartiCos())
	{
		fout << item.getTitlu() << "," << item.getAutor() << "," << item.getGen() << "," << item.getAn() << endl;
	}
}
const vector<Carte>& Biblioteca::getCartiCos() {
	return currentCos.getAllCartiCos();
}

void Biblioteca::adaugaCateva() {
addCarte("XXYYZZ", "MMM", "OOO", 1946);
	addCarte("AAAAA", "BVV", "GGG", 2003);
	addCarte("QQQQ", "EEEE", "ZZZ", 2020);
	addCarte("FFF", "AAA", "CCC", 1987);
	addCarte("LLL", "IIII", "TTT", 1932);
	addCarte("RRRR", "BBB", "FFFF", 1995);
	addCarte("EEEE", "NNN", "YYY", 1922);
	


}

void testAdaugaCtr() {
	CarteRepo rep;
	CarteValidator val;
	vector<UndoActions*> undo;
	Biblioteca ctr{ rep,val,undo };

	ctr.addCarte("a", "a", "a", 2000);
	assert(ctr.getAll().size() == 1);

	//adaug ceva invalid
	try {
		ctr.addCarte("", "", "", -1);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	//adaug ceva ce existadeja
	try {
		ctr.addCarte("a", "a", "a", -1);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}

	try {
		ctr.addCarte("Child in Time", "Deep Purple", "rock", 1946);
		assert(true);
	}
	catch (ValidateException&) {
		assert(false);
	}

	try {
		ctr.modificaCarte("Child in Time", "Deep Purple", "cyz", 1952);
		assert(true);
	}
	catch (ValidateException&) {
		assert(false);
	}

	try {
		ctr.modificaCarte("Child in Time", "Deep Purple", "", 1600);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}

	try {
		ctr.modificaCarte("wxyz", "Deep Purple", "fbsf", 1900);
		assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testFiltrare() {
	CarteRepo rep;
	CarteValidator val;
	vector<UndoActions*> undo;
	Biblioteca ctr{ rep,val,undo };
	ctr.addCarte("a", "a", "a", 1940);
	ctr.addCarte("b", "a", "x", 1980);
	ctr.addCarte("c", "a", "y", 2000);
	assert(ctr.filtrareAni(1930, 2000).size() == 3);
	assert(ctr.filtrareAni(1970, 2005).size() == 2);

	assert(ctr.filtrareAnMaiMic(1963).size() == 1);
	assert(ctr.filtrareAnMaiMic(1950).size() == 1);
	assert(ctr.filtrareAnMaiMic(1921).size() == 0);
	assert(ctr.filtrareAutor("a").size() == 3);
	assert(ctr.filtrareAutor("b").size() == 0);
	ctr.addCarte("Pasarea Calandrinon1", "Phoenix", "folk-rock", 1932);
	ctr.addCarte("Baba Novak1", "Phoenix", "folk-rock", 2003);
	ctr.addCarte("Apocalipsa1", "Phoenix", "folk-rock", 1995);
	ctr.addCarte("Fantanile1", "Alternosfera", "alternative rock", 1954);
	ctr.addCarte("Ploile Nu Vin1", "Alternosfera", "alternative rock", 2008);
	ctr.addCarte("Padure Verde1", "Via Daca", "maybe folk", 1971);

	ctr.stergeCarte("Apocalipsa1", "Phoenix");

	try {
		ctr.stergeCarte("shsbs", "Phoenix");
		assert(false);
	}

	catch (CarteRepoException&) {
		assert(true);
	}

}

void testSortare() {
	CarteRepo rep;
	CarteValidator val;
	vector<UndoActions*> undo;
	Biblioteca ctr{ rep,val,undo };
	ctr.addCarte("z", "z", "y", 1933);
	ctr.addCarte("b", "a", "d", 1978);
	ctr.addCarte("c", "a", "d", 1999);

	auto firstC = ctr.sortByTitlu()[0];
	assert(firstC.getTitlu() == "b");

	firstC = ctr.sortByAutor()[0];
	assert(firstC.getAutor() == "a");

	firstC = ctr.sortByGenAn()[0];
	assert(firstC.getAn() == 1978);

}

void testCos() {
	CarteRepo testRepo;
	CarteValidator testVal;
	vector<UndoActions*> undo;
	Biblioteca testService{ testRepo,testVal,undo };

	testService.addCarte("Pasarea Calandrinon", "Phoenix", "folk-rock", 1940);
	testService.addCarte("Baba Novak", "Phoenix", "folk-rock", 1980);
	testService.addCarte("Apocalipsa", "Phoenix", "folk-rock", 2000);
	testService.addCarte("Fantanile", "Alternosfera", "alternative rock", 1970);
	testService.addCarte("Ploile Nu Vin", "Alternosfera", "alternative rock", 1960);
	testService.addCarte("Padure Verde", "Via Daca", "maybe folk", 1990);

	testService.addRandomToCos(4);
	assert(testService.getCartiCos().size() == 4);
	testService.emptyCos();
	assert(testService.getCartiCos().size() == 0);

	testService.addRandomToCos(20);
	//putem adauga doar 6 melodii (fara sa se repete)
	assert(testService.getCartiCos().size() == 6);

	testService.emptyCos();
	testService.addToCos("Apocalipsa", "Phoenix");
	assert(testService.getCartiCos().size() == 1);

	try {
		testService.addToCos("Cocosii Negri", "Phoenix");
		assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}


}
void testCtr() {
	testAdaugaCtr();
	testFiltrare();
	testSortare();
	testCos();
}
