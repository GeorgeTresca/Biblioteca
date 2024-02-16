//
// Created by Andrei on 5/30/2023.
//

#ifndef ANDREI_OBSERVER_H
#define ANDREI_OBSERVER_H
#include "vector"

using namespace std;

class Observer {
public:
    virtual void update() = 0;
};

class observable {
private:
    vector<Observer*> lst;

public:
    void add_obs(Observer* o)
    {
        lst.push_back(o);
    }
    void notify_all()
    {
        for (auto a : lst)
        {
            a->update();
        }
    }

};


#endif //ANDREI_OBSERVER_H
