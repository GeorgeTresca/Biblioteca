#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QFormLayout>
#include <qboxlayout.h>
#include "Biblioteca.h"
#include "Carte.h"
#include <vector>
#include <qlabel.h>
#include "Observer.h"
#include <random>
#include <chrono>
#include <algorithm>
#include "service_bag.h"
#include "repo_bag.h"
#include "BagGui.h"



class SmallGUI : public QWidget {
private:
	QLabel* lbl = new QLabel("Nimic");
public:
	SmallGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		setLayout(ly);
		ly->addWidget(lbl);
	}

	void setCarte(const Carte& p) {
		lbl->setText(QString{ p.getGen().c_str() });
	}

};

class BibliotecaGUI : public QWidget,public Observer {
private:
	Biblioteca& ctr;
	service_cos& srv_cos;
	QListWidget* lst;
	QPushButton* btnSortByTitlu;
	QPushButton* btnSortByAutor;
	QPushButton* btnSortByGenAn;//
	QLineEdit* txtTitlu;
	QLineEdit* txtAutor;
	QLineEdit* txtGen;
	QLineEdit* txtAn;
	QLineEdit* txtUtil;
	
	QPushButton* btnAdd;
	QPushButton* btnDelete;
	QPushButton* btnModify;
	QPushButton* btnFilterByAutor;
	QPushButton* btnFilterByAnMaiMic;
	QPushButton* btnAfiseaza;
	QPushButton* btnUndo;
	QPushButton* btnAddCos;
	QPushButton* btnEmptyCos;
	QPushButton* btnRandomCos;
	//QPushButton* btnExportCos;


	//pentru cos
	/*QPushButton* addtobag = new QPushButton{"Adauga in cos"};
	QWidget* cos = new QWidget;
	QPushButton* golestebag = new QPushButton{ "Goleste cosul" };
	QPushButton* randombag = new QPushButton{ "Genereaza cos random" };
	QFormLayout* form = new QFormLayout;
	QListWidget* coslist = new QListWidget;
	QLineEdit* titlu_bag = new QLineEdit;
	QLineEdit* autor_bag = new QLineEdit;
	QLineEdit* gen_bag = new QLineEdit;
	QLineEdit* an_bag = new QLineEdit;

	*/

	QPushButton* addtobag = new QPushButton{ "Adauga in cos" };
	QWidget* cos = new QWidget;
	QPushButton* stergebag = new QPushButton{ "sterge din cos" };
	QFormLayout* form = new QFormLayout;
	QListWidget* coslist = new QListWidget;
	QLineEdit* denumire_bag = new QLineEdit;
	QLineEdit* destinatie_bag = new QLineEdit;
	QLineEdit* tip_bag = new QLineEdit;
	QLineEdit* nr_of_ntt_bag = new QLineEdit;
	QPushButton* afisare_aleator = new QPushButton{ "afisare aleator" };
	
	QLineEdit* exp_line = new QLineEdit;
	
	QWidget* read_only_cos = new QWidget;
	QVBoxLayout* mainread = new QVBoxLayout;
	QPushButton* read_only = new QPushButton{ "Cos(read only)" };
	BagGui read_only1{ srv_cos };
	QPushButton* addtobagmain = new QPushButton{ "Adauga in cos" };
	QPushButton* stergebagmain = new QPushButton{ "sterge din cos" };
	QPushButton* afisare_aleatormain = new QPushButton{ "afisare aleator" };
	QHBoxLayout* cosly = new QHBoxLayout;
	QLineEdit* line = new QLineEdit;


	void init_read_only()
	{
		mainread->addWidget(coslist);

	}

	void populate_srv()
	{
		ctr.addCarte("XXYYZZ", "MMM", "OOO", 1946);
		ctr.addCarte("AAAAA", "BVV", "GGG", 2003);
		ctr.addCarte("QQQQ", "EEEE", "ZZZ", 2020);
		ctr.addCarte("FFF", "AAA", "CCC", 1987);
		ctr.addCarte("LLL", "IIII", "TTT", 1932);
		ctr.addCarte("RRRR", "BBB", "FFFF", 1995);
		ctr.addCarte("EEEE", "NNN", "YYY", 1922);
	}
	void initGUICmps();
	void bag_init();
	//void add_to_bag();
	void randomBag();
	void load_data_to_bag();
	void initFereastraCos();
	void connectSignalsSlots();
	void reloadList(const std::vector<Carte>& carti);
	void addNewCarte();
	void deleteCarte();
	void modifyCarte();
	void filterByAutor();
	void undo();
	void add_to_bag();
	void Shuffle();
	void Shuffle1();
	void load_data_to_bag1(vector<Carte>carti);


public:
	BibliotecaGUI(Biblioteca& ctr, service_cos& cos) :ctr{ ctr }, srv_cos{cos} {
		initGUICmps();
		connectSignalsSlots();
		populate_srv();
		bag_init();
		reloadList(ctr.getAll());
		//load_data_to_bag();
		
	}

	void update()override {
		load_data_to_bag();
	}

};

