#include "BibliotecaGUI.h"
#include "Carte.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include <algorithm>


void BibliotecaGUI::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub trei butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lst = new QListWidget;
	vl->addWidget(lst);

	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByTitlu = new QPushButton("Sort by titlu");
	lyBtnsDr->addWidget(btnSortByTitlu);

	btnSortByAutor = new QPushButton("Sort by Autor");
	lyBtnsDr->addWidget(btnSortByAutor);

	btnSortByGenAn = new QPushButton("Sort by Gen si An");
	lyBtnsDr->addWidget(btnSortByGenAn);

	btnAfiseaza=new QPushButton("Afiseaza carti");
	lyBtnsDr->addWidget(btnAfiseaza);

	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtTitlu = new QLineEdit;
	formLDetalii->addRow(new QLabel("Titlu:"), txtTitlu);
	txtAutor = new QLineEdit;
	formLDetalii->addRow(new QLabel("Autor:"), txtAutor);
	txtGen = new QLineEdit;
	formLDetalii->addRow(new QLabel("Gen:"), txtGen);
	txtAn = new QLineEdit;
	formLDetalii->addRow(new QLabel("An:"), txtAn);
	txtUtil = new QLineEdit;
	formLDetalii->addRow(new QLabel("Nr int:"), txtUtil);

	btnAdd = new QPushButton("Adauga carte");

	formLDetalii->addWidget(btnAdd);

	btnDelete=new QPushButton("Sterge carte");

	formLDetalii->addWidget(btnDelete);

	btnModify=new QPushButton("Modifica carte");

	formLDetalii->addWidget(btnModify);

	btnFilterByAutor=new QPushButton("Filtreaza dupa autor");
	formLDetalii->addWidget(btnFilterByAutor);

	btnFilterByAnMaiMic=new QPushButton("Filtreaza dupa an mai mic");
	formLDetalii->addWidget(btnFilterByAnMaiMic);

	btnUndo=new QPushButton("Undo");
	formLDetalii->addWidget(btnUndo);

	
	formLDetalii->addWidget(addtobagmain);
	formLDetalii->addWidget(stergebagmain);
	formLDetalii->addWidget(afisare_aleatormain);

	
	ly->addWidget(widDetalii);
}

/*void BibliotecaGUI::bag_init()
{
	auto mainlybag = new QVBoxLayout;
	mainlybag->addWidget(coslist);

	//titlu_bag->setPlaceholderText(QString::fromStdString("Titlu"));
	//autor_bag->setPlaceholderText(QString::fromStdString("Autor"));
	//gen_bag->setPlaceholderText(QString::fromStdString("Gen"));
	//an_bag->setPlaceholderText(QString::fromStdString("An"));
	QWidget* widDetalii2 = new QWidget;
	QFormLayout* formLDetalii2 = new QFormLayout;
	widDetalii2->setLayout(formLDetalii2);
	titlu_bag = new QLineEdit;
	formLDetalii2->addRow(new QLabel("Titlu:"), titlu_bag);
	autor_bag = new QLineEdit;
	formLDetalii2->addRow(new QLabel("Autor:"), autor_bag);
	gen_bag = new QLineEdit;
	formLDetalii2->addRow(new QLabel("Gen:"), gen_bag);
	an_bag = new QLineEdit;
	formLDetalii2->addRow(new QLabel("An:"), an_bag);
	
	auto secondbagly = new QVBoxLayout;
	secondbagly->addLayout(form);
	mainlybag->addWidget(golestebag);
	mainlybag->addLayout(secondbagly);
	mainlybag->addWidget(widDetalii2);
	cos->setLayout(mainlybag);
	load_data_to_bag();
}
*/

void BibliotecaGUI::bag_init()
{
	srv_cos.add_obs(this);
	srv_cos.add_obs(&read_only1);
	auto primbag = new QHBoxLayout;
	auto mainlybag = new QVBoxLayout;
	mainlybag->addWidget(coslist);
	auto secondlybag = new QVBoxLayout;
	denumire_bag->setPlaceholderText(QString::fromStdString("Denumire"));
	destinatie_bag->setPlaceholderText(QString::fromStdString("Destinatie"));
	tip_bag->setPlaceholderText(QString::fromStdString("tip"));
	//pret_bag->setPlaceholderText(QString::fromStdString("pret"));
	auto secondbagly = new QVBoxLayout;
	secondbagly->addLayout(form);
	mainlybag->addWidget(stergebag);
	//mainlybag->addWidget(afisare_aleator);
	mainlybag->addLayout(secondbagly);
	cos->setLayout(primbag);
	nr_of_ntt_bag->setPlaceholderText("numar de entitati");
	secondlybag->addWidget(nr_of_ntt_bag);
	secondlybag->addWidget(afisare_aleator);
	
	primbag->addLayout(mainlybag);
	primbag->addLayout(secondlybag);
	load_data_to_bag();
}

//functie care afiseaza lista de vacante din cos
void BibliotecaGUI::load_data_to_bag()
{
	coslist->clear();
	for (const auto elem : srv_cos.srv_get_all_bag())
	{
		auto item = new QListWidgetItem(QString::fromStdString(elem.getTitlu()));
		item->setData(Qt::UserRole, QString::fromStdString(elem.getAutor()));
		coslist->addItem(item);
	}
}

void BibliotecaGUI::load_data_to_bag1(vector<Carte> carti)
{
	coslist->clear();
	for (const auto& elem : carti)
	{
		auto item = new QListWidgetItem(QString::fromStdString(elem.getTitlu()));
		item->setData(Qt::UserRole, QString::fromStdString(elem.getAutor()));
		coslist->addItem(item);
	}
}


void BibliotecaGUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByTitlu, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByTitlu());
		load_data_to_bag1(srv_cos.sortare_dupa_titlu());
		
		
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByAutor, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByAutor());
		load_data_to_bag1(srv_cos.sortare_dupa_autor());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByGenAn, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByGenAn());
		});
	//cand se selecteaza elementul din lista incarc detaliile
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		if (lst->selectedItems().isEmpty()) {
			//nu este nimic selectat (golesc detaliile)
			txtTitlu->setText("");
			txtAutor->setText("");
			txtGen->setText("");
			txtAn->setText("");
			return;
		}
		QListWidgetItem* selItem = lst->selectedItems().at(0);
		QString titlu = selItem->text();
		txtTitlu->setText(titlu);
		QString autor = selItem->data(Qt::UserRole).toString();
		txtAutor->setText(autor);
		try {
			//cautam Carte
			Carte p = ctr.find(titlu.toStdString(), autor.toStdString());
			txtGen->setText(QString::fromStdString(p.getGen()));
			txtAn->setText(QString::number(p.getAn()));
		}
		catch (CarteRepoException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));

		}
		});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &BibliotecaGUI::addNewCarte);
	QObject::connect(btnDelete, &QPushButton::clicked, this, &BibliotecaGUI::deleteCarte);
	QObject::connect(btnModify, &QPushButton::clicked, this, &BibliotecaGUI::modifyCarte);
	QObject::connect(btnFilterByAutor, &QPushButton::clicked, [&]() {
		reloadList(ctr.filtrareAutor(txtAutor->text().toStdString()));
		});
	QObject::connect(btnAfiseaza, &QPushButton::clicked, [&]() {
		
		
		reloadList(ctr.getAll());
		});
	QObject::connect(btnFilterByAnMaiMic, &QPushButton::clicked, [&]() {
		reloadList(ctr.filtrareAnMaiMic(txtAn->text().toInt()));
		});
	QObject::connect(btnUndo, &QPushButton::clicked, this, &BibliotecaGUI::undo);

	//QObject::connect(addtobag, &QPushButton::clicked, [&]() {
		//add_to_bag();

		//cos->show();
		//});

	//connect the addtobag button 


	QObject::connect(addtobag, &QPushButton::clicked, [&]() {
		add_to_bag();

		cos->show();
		});

	QObject::connect(addtobagmain, &QPushButton::clicked, [&]() {
		add_to_bag();
		cos->show();
		});

	QObject::connect(coslist, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = coslist->selectedItems();
		if (sel.empty())
		{
			denumire_bag->setText("");
			destinatie_bag->setText("");
			tip_bag->setText("");
			//pret_bag->setText("");

		}
		else
		{
			auto bag_item = sel.at(0);
			auto dest = bag_item->text().toStdString();
			auto den = bag_item->data(Qt::UserRole).toString().toStdString();
			auto v = srv_cos.find(den, dest);
			denumire_bag->setText(QString::fromStdString(v.getTitlu()));
			destinatie_bag->setText(QString::fromStdString(v.getAutor()));
			tip_bag->setText(QString::fromStdString(v.getGen()));
			//pret_bag->setText(QString::number(v.getDurata()));
		}
		});

	QObject::connect(stergebag, &QPushButton::clicked, [&]() {
		srv_cos.srv_delete();
		load_data_to_bag();
		});
	QObject::connect(stergebagmain, &QPushButton::clicked, [&]() {
		srv_cos.srv_delete();
		load_data_to_bag();
		});
	QObject::connect(afisare_aleator, &QPushButton::clicked, [&]() {
		Shuffle();
		load_data_to_bag();
		});
	QObject::connect(afisare_aleatormain, &QPushButton::clicked, [&]() {
		Shuffle1();
		load_data_to_bag();
		cos->show();
		});

	QObject::connect(read_only, &QPushButton::clicked, [&]() {
		auto a = new BagGui{ srv_cos };
		srv_cos.add_obs(a);
		a->show();
		});
	/*
	QObject::connect(btnRandomCos, &QPushButton::clicked, [&]() {
		randomBag();
		cos->show();
		});

	//pwntru afisare
	QObject::connect(coslist, &QListWidget::itemSelectionChanged, [&]() {
		/*auto sel = coslist->selectedItems();
		if (sel.empty())
		{
			titlu_bag->setText("");
			autor_bag->setText("");
			gen_bag->setText("");
			an_bag->setText("");

		}
		else
		{
			auto bag_item = sel.at(0);
			auto dest = bag_item->text().toStdString();
			auto den = bag_item->data(Qt::UserRole).toString().toStdString();
			auto v = ctr.findCos(den, dest);
			titlu_bag->setText(QString::fromStdString(v.getTitlu()));
			autor_bag->setText(QString::fromStdString(v.getAutor()));
			gen_bag->setText(QString::fromStdString(v.getGen()));
			an_bag->setText(QString::number(v.getAn()));
		}


		if (coslist->selectedItems().isEmpty()) {
			//nu este nimic selectat (golesc detaliile)
			titlu_bag->setText("");
			autor_bag->setText("");
			gen_bag->setText("");
			an_bag->setText("");
			return;
		}
		QListWidgetItem* selItem = coslist->selectedItems().at(0);
		QString titlu = selItem->text();
		titlu_bag->setText(titlu);
		QString autor = selItem->data(Qt::UserRole).toString();
		autor_bag->setText(autor);
		try {
			//cautam Carte
			Carte p = ctr.findCos(titlu.toStdString(), autor.toStdString());
			gen_bag->setText(QString::fromStdString(p.getGen()));
			an_bag->setText(QString::number(p.getAn()));
		}
		catch (CarteRepoException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));

		}
		});
	*/
}

void BibliotecaGUI::addNewCarte() {
	try {
		ctr.addCarte(txtTitlu->text().toStdString(), txtAutor->text().toStdString(), txtGen->text().toStdString(), txtAn->text().toInt());
		reloadList(ctr.getAll());
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (CarteRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void BibliotecaGUI::deleteCarte() {
	try {
		srv_cos.srv_delete_carte(txtTitlu->text().toStdString(), txtAutor->text().toStdString());
		ctr.deleteCarte(txtTitlu->text().toStdString(), txtAutor->text().toStdString(), txtGen->text().toStdString(), txtAn->text().toInt());
		reloadList(ctr.getAll());
		
		load_data_to_bag();
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (CarteRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void BibliotecaGUI::modifyCarte() {
	try {
		ctr.modificaCarte1(txtTitlu->text().toStdString(), txtAutor->text().toStdString(), txtGen->text().toStdString(), txtAn->text().toInt());
		reloadList(ctr.getAll());
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (CarteRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void BibliotecaGUI::undo() {
	try {
		ctr.doUndo();
		reloadList(ctr.getAll());
	}
	catch (CarteRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch  (std::exception()){
		QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se mai poate face Undo"));
	}
}

void BibliotecaGUI::add_to_bag()
{
	try
	{
		srv_cos.srv_add(txtTitlu->text().toStdString(), txtAutor->text().toStdString());
		load_data_to_bag();
	}
	catch (CarteRepoException& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
}
void BibliotecaGUI::Shuffle()
{
	vector<Carte> lst = ctr.getAll();
	auto n = nr_of_ntt_bag->text().toInt();
	while (n) {
		mt19937 mt{ random_device{}() };
		uniform_int_distribution<> dist(0, lst.size() - 1);
		int randomNr = dist(mt);
		auto seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(lst.begin(), lst.end(), default_random_engine(seed));
		srv_cos.srv_add(lst[randomNr].getTitlu(), lst[randomNr].getAutor());
		n--;
	}
}
void BibliotecaGUI::Shuffle1()
{
	vector<Carte> lst = ctr.getAll();
	auto n = txtUtil->text().toInt();
	while (n) {
		mt19937 mt{ random_device{}() };
		uniform_int_distribution<> dist(0, lst.size() - 1);
		int randomNr = dist(mt);
		auto seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(lst.begin(), lst.end(), default_random_engine(seed));
		srv_cos.srv_add(lst[randomNr].getTitlu(), lst[randomNr].getAutor());
		n--;
	}
}

/*void BibliotecaGUI::load_data_to_bag()
{
	coslist->clear();
	for (const auto elem : ctr.getCartiCos())
	{
		auto item = new QListWidgetItem(QString::fromStdString(elem.getTitlu()));
		item->setData(Qt::UserRole, QString::fromStdString(elem.getAutor()));
		coslist->addItem(item);
	}
}
*/
void BibliotecaGUI::reloadList(const std::vector<Carte>& carti) {
	//auto colorize = ctr.getFilterByPrice(20);
	lst->clear();
	for (const auto& p : carti) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getTitlu()), lst);
		item->setData(Qt::UserRole, QString::fromStdString(p.getAutor()));//adaug in lista (invizibil) si type 
		
	}
}