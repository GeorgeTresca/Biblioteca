//
// Created by Andrei on 4/20/2023.
//

#include "service_bag.h"
#include <cassert>
#include <fstream>
void service_cos::srv_add(string titlu, string autor) {
    bag_repo.repo_add(song_repo.find(titlu, autor));
    this->notify_all();

}

void service_cos::srv_delete() {
    bag_repo.repo_delete();
    this->notify_all();

}

void service_cos::srv_delete_carte(string titlu, string autor) {
	bag_repo.repo_delte(song_repo.find(titlu, autor));
	this->notify_all();

}

vector<Carte> service_cos::srv_get_all_bag() {
    return bag_repo.get_bag();
}

vector<Carte> service_cos::sortare_dupa_titlu() {
	vector<Carte> bag = srv_get_all_bag();
	for (int i = 0; i < bag.size() - 1; i++)
		for (int j = i + 1; j < bag.size(); j++)
			if (bag[i].getTitlu() > bag[j].getTitlu())
				swap(bag[i], bag[j]);
	return bag;
}

vector<Carte> service_cos::sortare_dupa_autor() {
	vector<Carte> bag = srv_get_all_bag();
	for (int i = 0; i < bag.size() - 1; i++)
		for (int j = i + 1; j < bag.size(); j++)
			if (bag[i].getAutor() > bag[j].getAutor())
				swap(bag[i], bag[j]);
	return bag;
}

/*void service_cos::Bag_Export(string& fisier, int& option) {

    if (option == 1)
        fisier += ".cvs";
    else
        fisier += ".html";
    ofstream fout(fisier);
    for (auto item : srv_get_all_bag())
    {
        fout << item.getArtist() << "," << item.getTitlu() << "," << item.getGen() << "," << item.getDurata() << endl;
    }
}
*/

Carte service_cos::find(string denumire, string destinatie) {
    for (const auto& s : bag_repo.get_bag())
    {
        if (s.getTitlu() == denumire && s.getAutor() == destinatie)
            return s;
    }
    return Carte();
}


void test_add_delete_get_srv()
{
    CarteRepo test_repo;
    Carte song1{ "Pictures of Home", "Deep Purple", "rock",1933 };
    Carte song2{ "Highway Star","Deep Purple", "rock",2000 };
    Carte song3{ "Holy Diver","Dio", "rock", 2004 };
    test_repo.store(song1);
    test_repo.store(song2);
    test_repo.store(song3);
    repo_cos cos;
    service_cos srv{ cos,test_repo };
    srv.srv_add("Pictures of Home", "Deep Purple");
    srv.srv_add("Highway Star", "Deep Purple");
    srv.srv_add("Holy Diver", "Dio");
    assert(srv.srv_get_all_bag().size() == 3);
    srv.srv_delete();
    assert(srv.srv_get_all_bag().size() == 0);
}

void test_srv_cos() {
    test_add_delete_get_srv();
}
