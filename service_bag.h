//
// Created by Andrei on 4/20/2023.
//

#ifndef ANDREI_SERVICE_COS_H
#define ANDREI_SERVICE_COS_H
#include "repo_bag.h"
#include "Repo.h"
#include <vector>
#include <string>
#include "Observer.h"
using namespace std;
class service_cos : public observable {
private:
    repo_cos& bag_repo;
    CarteRepo& song_repo;
public:
    service_cos(repo_cos& repo, CarteRepo& songrepo) :bag_repo{ repo }, song_repo{ songrepo } {};
    void srv_add(string denumire, string destinatie);

    void srv_delete();
    void srv_delete_carte(string titlu, string autor);
    vector<Carte> srv_get_all_bag();
    vector<Carte> sortare_dupa_titlu() ;
    vector<Carte> sortare_dupa_autor(); 
    //void Bag_Export(string& fisier, int& option);
    Carte find(string denumire, string destinatie);
};

void test_srv_cos();
#endif //ANDREI_SERVICE_COS_H
