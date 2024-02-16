#include "console.h"
#include "Biblioteca.h"
#include "Repo.h"
#include "Validator.h"
#include <QtWidgets/QApplication>
#include "BibliotecaGUI.h"
#include "repo_bag.h"
#include "service_bag.h"


void testAll() {
	testeDomain();
	cout << "Finished teste Domain\n";
	testeRepo();
	cout << "Finished teste Repo\n";
	testCtr();
	cout << "Finished teste Ctr\n";
	testValidator();
	cout << "Finished teste Validator\n";
	test_repo_cos();
	cout << "Finished teste Repo Bag\n";
	test_srv_cos();



}

int main(int argc, char* argv[]) {
	testAll();

	/*CarteRepo rep;
	CarteValidator val;
	vector<UndoActions*> undo;
	Biblioteca ctr{ rep,val,undo };
	//adaugaCateva(ctr);//adaug cateva animale
	ConsolUI ui{ ctr };
	ui.start();*/
	{
		QApplication a(argc, argv);
		//PetRepo rep;
		CarteRepo rep;
		CarteValidator val;
		vector<UndoActions*> undo;
		repo_cos bag_repo;
		service_cos srv_bag{ bag_repo,rep };

		

		Biblioteca ctr{ rep,val,undo };
		//ctr.adaugaCateva();
		BibliotecaGUI gui{ ctr , srv_bag};
		gui.show();
		
		return QApplication::exec();



		
		//a.exec();
	}

}
