//
// Created by Andrei on 4/20/2023.
//

#include "repo_bag.h"
#include <cassert>
void repo_cos::repo_add(Carte s) {
    bag.push_back(s);
}

void repo_cos::repo_delete() {
    bag.clear();
}

vector<Carte> repo_cos::get_bag() {
    return bag;
}

void repo_cos::repo_delte(Carte s) {
    for (int i = 0; i < bag.size(); i++)
    {
		if (bag[i].getTitlu() == s.getTitlu()&&bag[i].getAutor()==s.getAutor())
			bag.erase(bag.begin() + i);
	}
}

void test_add_delete_get_all()
{
    repo_cos s;
    Carte song1{ "Pictures of Home", "Deep Purple", "rock",1955 };
    Carte song2{ "Highway Star","Deep Purple", "rock",1934 };
    Carte song3{ "Holy Diver","Dio", "rock", 2000 };
    Carte song4{ "Holy Diver","Dio", "city", 2003 };
    s.repo_add(song1);
    s.repo_add(song2);
    s.repo_add(song3);
    s.repo_add(song4);
    assert(s.get_bag().size() == 4);
    s.repo_delete();
    assert(s.get_bag().empty());
}



void test_repo_cos() {
    test_add_delete_get_all();
}
