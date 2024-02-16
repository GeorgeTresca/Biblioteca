#pragma once
#include "UndoActions.h"

class UndoModifica : public UndoActions {

public:
    UndoModifica(CarteRepo& repo, Carte& s) : UndoActions{ repo,s } {}
    void DoUndo() override;
    ~UndoModifica() = default;

};
