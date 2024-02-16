#pragma once

#include "Carte.h"
#include "Repo.h"
class UndoActions {
protected:
    CarteRepo& repo;
    Carte  v;
public:
    //ActiuneUndo()=default;
    UndoActions(CarteRepo& r, Carte& v) :repo{ r }, v{ v } {};
    virtual void DoUndo() = 0;
    ~UndoActions() = default;
};
