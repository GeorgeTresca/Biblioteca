#pragma once

#include "UndoActions.h"

class UndoSterge : public UndoActions {
public:
    UndoSterge(CarteRepo& r, Carte& s) : UndoActions{ r, s } {};
    void DoUndo() override;
    ~UndoSterge() = default;
};
