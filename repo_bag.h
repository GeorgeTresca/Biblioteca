//
// Created by Andrei on 4/20/2023.
//

#ifndef ANDREI_REPO_COS_H
#define ANDREI_REPO_COS_H
#include <vector>
#include "Carte.h"
using namespace std;
class repo_cos {

private:
    vector<Carte> bag;
public:
    void repo_add(Carte s);
    void repo_delete();
    void repo_delte(Carte s);
    vector<Carte> get_bag();

};

void test_repo_cos();


#endif //ANDREI_REPO_COS_H
