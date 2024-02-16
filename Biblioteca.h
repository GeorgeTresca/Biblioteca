
#pragma once

#include "Carte.h"
#include "Repo.h"
#include <string>
#include <vector>
#include <functional>
#include "Cos.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include "UndoActions.h"
#include "UndoAdauga.h"
#include "UndoSterge.h"
#include "UndoModifica.h"


using std::vector;
using std::function;

class Biblioteca {
	CarteRepo& rep;
	CarteValidator& val;
	vector<UndoActions*>& Undo;
	Cos currentCos;
	
	/*
	 Functie de sortare generala
	 maiMareF - functie care compara 2 Carte, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Carte)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<Carte> generalSort(bool (*maiMicF)(const Carte&, const Carte&));
	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar carti care trec de filtru (fct(carte)==true)
	*/
	vector<Carte> filtreaza(function<bool(const Carte&)> fct);

public:
	Biblioteca(CarteRepo& rep, CarteValidator& val, vector<UndoActions*>& u) :rep{ rep }, val{ val }, Undo{ u } {}
	//nu permitem copierea de obiecte Biblioteca
	Biblioteca(const Biblioteca& ot) = delete;
	/*
	 returneaza toate cartile in ordinea in care au fost adaugate
	*/
	const vector<Carte>& getAll() noexcept {
		return rep.getAll();
	}
	/*
	Adauga o noua Carte
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addCarte(const string& titlu, const string& autor, const string& gen, int an);

	Carte find(const string& titlu, const string& autor);

	void modificaCarte(string titlu, string autor, string noulGen, int noulAn);

	void stergeCarte(string titlu, string autor);

	void deleteCarte(string titlu, string autor, string gen, int an);

	void modificaCarte1(string titlu, string autor, string gen, int an);

	void doUndo();

	/*
	Sorteaza dupa titlu
	*/
	vector<Carte> sortByTitlu();

	/*
	Sorteaza dupa autor
	*/
	vector<Carte> sortByAutor();


	/*
	Sorteaza dupa gen+an
	*/
	vector<Carte> sortByGenAn();

	/*
	returneaza doar cartile cu an mai mic decat cel dat
	*/
	vector<Carte> filtrareAnMaiMic(int an);

	/*
	returneaza doar cartile cu an intre cei doi ani
	*/
	vector<Carte> filtrareAni(int anMin, int anMax);

	vector<Carte> filtrareAutor(const string& autor);

	/*
	* Adauga o carte cu titlu titlu si aautor in cos
	*
	* @param titlu: titlul cartii care se adauga (string)
	* @param autorul: autorul melodiei care se adauga (string)
	*
	* post: cartea este adaugata in cos
	* @throws: RepoException daca nu exista carte cu titlu si autor dat
	*/
	void addToCos(string titlu, string autor);
	/*
	* Adauga un numar random de carti in cos
	*
	* @param howMany: cate carti se adauga (int)
	*
	* @return: numarul de carti adaugate in cos
	* post: se adauga un numar random de carti in cos
	*/
	int addRandomToCos(int howMany);
	/*
	* Elimina toate cartile din cos
	* post: cosul nu contine nicio carte
	*/
	void emptyCos();

	Carte findCos(string titlu, string autor);

	void Export_Cos(string& fisier, int& option);
	/*
	* Returneaza un vector cu toate cartile din cos
	*/
	const vector<Carte>& getCartiCos();
	
	void adaugaCateva();

};
void testCtr();

