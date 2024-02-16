#pragma once
#include "Carte.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock

using std::vector;
class Cos {
private:
	vector<Carte> cosCarti;
public:
	Cos() = default;
	/*
	* Adauga o carte in cos
	* @param s: cartea care se adauga (Carte)
	*
	* post: cartea va fi adaugata in cos
	*/
	void addCarteinCos(const Carte& s);
	/*
	* Elimina toate cartile din cos
	* post: cosul este gol
	*/
	void emptyCos();
	/*
	* Adauga un numar random de carti in cos
	*
	* @param originalCarti: cartile din care se alege (vector<Carte>)
	* @param howMany: cate carti se adauga (int)
	*
	* post: cartile sunt adaugate in cosul curent
	*/
	void addRandomCarti(vector<Carte> originalCarti, int howMany);
	/*
	* Returneaza un vector care contine toate cartile din cos
	*/
	const vector<Carte>& getAllCartiCos();
};

