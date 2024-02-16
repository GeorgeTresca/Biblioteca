#pragma once
#include "UndoActions.h"

class UndoAdauga : public UndoActions {
public:
    UndoAdauga(CarteRepo& repo, Carte& s) : UndoActions{ repo, s } {}
    void DoUndo() override;
    ~UndoAdauga() = default;

};
