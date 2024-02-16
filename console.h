#pragma once
#include "Biblioteca.h"
#include "Carte.h"
class ConsolUI {
	Biblioteca& ctr;
	/*
	Citeste datele de la tastatura si adauga Carte
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaUI();

	void modificaUI();
	void stergeUI();

	void uiCos();
	void uiAddToCos();
	void uiAddRandomToCos();
	void uiEmptyCos();
	void uiExportCos();
	void addDefaultCarti();
	void uiModify();
	void uiDelete();
	void UNDO();
	void uiModifyCarte();
	void uiDeleteCarte();
	void printMenu();
	void printCosMenu();

	void addDefaulCarti();
	/*
	Tipareste o lista de carti la consola
	*/
	void tipareste(const vector<Carte>& carti);
public:
	ConsolUI(Biblioteca& ctr) :ctr{ ctr } {
	}
	//nu permitem copierea obiectelor
	ConsolUI(const ConsolUI& ot) = delete;

	void start();
};
