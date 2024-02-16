#include "console.h"

#include "Carte.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using namespace std;
using std::string;
void ConsolUI::tipareste(const vector<Carte>& carti) {
	cout << "\nCarti:\n";
	for (const auto& carte : carti) {
		cout << ' ' << carte.getTitlu() << ' ' << carte.getAutor() << ' ' << carte.getGen() << ' ' << carte.getAn() << '\n';
	}
	cout << "\nSfarsit lista de carti\n\n";
}

void ConsolUI::adaugaUI() {
	string ti, au, gen;
	int an;
	cout << "Dati titlu:";
	cin >> ti;
	cout << "Dati autor:";
	cin >> au;
	cout << "Dati gen:";
	cin >> gen;
	cout << "Dati an:";
	cin >> an;
	while (an < 1800 || an>2023) {
		cout << "An invalid\nDati an:";
		cin >> an;

	}
	ctr.addCarte(ti, au, gen, an);
	cout << "Adaugat cu succes\n\n";
}

void ConsolUI::uiModify() {
	string titlu, autor, gen;
	int an_ap;
	cout << "Titlul cartii este:";
	getline(cin >> ws, titlu);

	cout << "Autorul cartii este:";
	getline(cin >> ws, autor);
	cout << "Noul gen al cartii este:";
	getline(cin >> ws, gen);

	cout << "Noul an al aparitiei cartii (numar intreg intre 1800 si 2023) este:";
	cin >> an_ap;
	while (an_ap < 1800 || an_ap>2023) {
		cout << "An invalid\nDati an:";
		cin >> an_ap;

	}
	try {
		ctr.modificaCarte(titlu, autor, gen, an_ap);
		cout << "Carte modificata cu succes!\n" << endl;
	}
	catch (CarteRepoException& re) {
		cout << re;
	}
	catch (ValidateException& ve) {
		cout << "Cartea nu este valida!\n" << endl;
		cout << ve;
	}

}

void ConsolUI::uiDelete() {
	string titlu, autor;

	cout << "Titlul cartii este:";
	getline(cin >> ws, titlu);

	cout << "Autorul cartii este:";
	getline(cin >> ws, autor);

	try {
		ctr.stergeCarte(titlu, autor);
		cout << "Stergere realizata cu succes!\n" << endl;
	}
	catch (CarteRepoException& re) {
		cout << re;
	}

}

void ConsolUI::uiDeleteCarte() {
	string titlu, artist, gen;
	int an;
	cout << "Introduceti titlul:";
	getline(cin >> ws, titlu);

	cout << "Introduceti autorul:";
	getline(cin >> ws, artist);
	cout << "introduceti genul:";
	getline(cin >> ws, gen);

	cout << "introduceti anul:";
	cin >> an;
	try {
		ctr.deleteCarte(titlu, artist, gen, an);
	}
	catch (CarteRepoException& re) {
		cout << re;
	}
	catch (ValidateException& ve) {
		cout << "Cartea nu este valida!" << endl;
		cout << ve;
	}
}

void ConsolUI::uiModifyCarte() {
	string titlu, artist, gen;
	int an;
	cout << "Introduceti titlu:";
	getline(cin >> ws, titlu);

	cout << "Introduceti autor:";
	getline(cin >> ws, artist);
	cout << "introduceti genul:";
	getline(cin >> ws, gen);

	cout << "introduceti anul:";
	cin >> an;
	try {
		ctr.modificaCarte1(titlu, artist, gen, an);
	}
	catch (CarteRepoException& re) {
		cout << re;
	}
	catch (ValidateException& ve) {
		cout << "Oferta nu este valida!" << endl;
		cout << ve;
	}

}

void ConsolUI::UNDO() {
	try {
		ctr.doUndo();

	}
	catch (string& ex)
	{

		cout << ex;
	}

}

void ConsolUI::uiAddToCos() {
	string titlu, autor;
	cout << "Titlul cartii este:";
	getline(cin >> ws, titlu);

	cout << "Autorul cartii este:";
	getline(cin >> ws, autor);

	try {
		ctr.addToCos(titlu, autor);
		cout << "Cartea s-a adaugat cu succes in cos.\n" << endl;
	}
	catch (CarteRepoException& re) {
		cout << re;
	}
	catch (ValidateException& ve) {
		cout << "Cartea nu este valida!\n" << endl;
		cout << ve;
	}
}
void ConsolUI::uiAddRandomToCos() {
	int howManyToAdd;
	cout << "Cate carti sa se adauge in cos?";
	cin >> howManyToAdd;


	try {
		int howManyAdded = ctr.addRandomToCos(howManyToAdd);
		cout << "S-au adaugat " << howManyAdded << " carti in playlist.\n" << endl;
	}
	catch (CarteRepoException& re) {
		cout << re;
	}
}


void ConsolUI::uiEmptyCos() {
	ctr.emptyCos();
	cout << "S-au sters toate cartile din playlist-ul curent.\n" << endl;
}


void ConsolUI::uiExportCos() {
	string fisier;
	int optiune;
	cout << "Introduceti numele fisierului\n";
	getline(cin >> ws, fisier);
	cout << "Introduceti optiunea:";
	cin >> optiune;
	if (ctr.getCartiCos().empty())
		cout << "Cosul este gol!\n";
	else
		ctr.Export_Cos(fisier, optiune);

}

void ConsolUI::printMenu() {
	cout << "\nMeniu:\n";
	cout << "1. adauga\n2. tipareste\n3. sort by titlu\n4. sort by autor\n5. sort by gen+an\n6. filtrare an\n7. Filtrare an min max\n8. Filtrare autor\n9. Modifica\n10. Sterge\n11. Meniu Cos\n12.Undo\n0. Iesire\nDati comanda:";
}

void ConsolUI::printCosMenu() {
	cout << "\nMENIU COS\n" << endl;
	cout << "1. Adauga carte in cos" << endl;
	cout << "2. Adauga carti random in cos" << endl;
	cout << "3. Goleste cos" << endl;
	cout << "4. Afiseaza cos curent" << endl;
	cout << "5. Afiseaza cos curent in fisier" << endl;
	cout << "6. Inapoi la meniul principal" << endl;
}

void ConsolUI::uiCos() {
	int cmd;
	int runningPlayList = 1;
	while (runningPlayList) {
		printCosMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAddToCos();
			break;
		case 2:
			uiAddRandomToCos();
			break;
		case 3:
			uiEmptyCos();
			break;

		case 4:
			tipareste(ctr.getCartiCos());
			break;

		case 5:
			uiExportCos();
			break;
		case 6:
			runningPlayList = 0;
			break;
		default:

			break;

			//continue;
		}

	}
}

void ConsolUI::addDefaultCarti() {
	ctr.addCarte("abcd", "aaaa", "www", 1947);
	ctr.addCarte("whyf", "pingd", "www", 1999);
	ctr.addCarte("nfbd", "bbb", "rrr", 2010);
	ctr.addCarte("ccccc", "aaaa", "eeee", 1988);
	ctr.addCarte("nbvd", "aaaa", "gngd", 2003);
	ctr.addCarte("nnn", "ddd", "eeee", 1972);
	ctr.addCarte("qwdqc", "bbb", "bfdbfs", 1931);
	ctr.addCarte("vvvvv", "ttt", "mnnb", 1965);

}

void ConsolUI::start() {
	addDefaultCarti();
	while (true) {
		printMenu();
		int cmd;
		cin >> cmd;
		try {
			switch (cmd) {
			case 1: {
				adaugaUI();
				break; }
			case 2: {
				tipareste(ctr.getAll());
				break; }
			case 3: {
				tipareste(ctr.sortByTitlu());
				break; }
			case 4: {
				tipareste(ctr.sortByAutor());
				break; }
			case 5: {
				tipareste(ctr.sortByGenAn());
				break; }
			case 6: {
				cout << "Dati an maxim:";
				int an;
				cin >> an;
				tipareste(ctr.filtrareAnMaiMic(an));
				break; }
			case 7: {
				cout << "Dati an minim:";
				int anMin;
				cin >> anMin;
				cout << "Dati an maxim:";
				int anMax;
				cin >> anMax;
				tipareste(ctr.filtrareAni(anMin, anMax));
				break; }
			case 8: {
				string aut;
				cout << "Dati autor:";

				cin >> aut;
				tipareste(ctr.filtrareAutor(aut));
				break;
			}
			case 9: {
				uiModifyCarte();
				break;
			}
			case 10: {
				uiDeleteCarte();
				break;
			}
			case 11: {
				uiCos();
				break;

			}
			case 12: {
				UNDO();
				break;
			}
			case 0: {
				return; }
			default: {
				cout << "Comanda invalida\n";
				break;
			}
			}
		}
		catch (const CarteRepoException& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException& ex) {
			cout << ex << '\n';
		}
	}
}