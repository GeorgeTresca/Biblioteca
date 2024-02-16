#include "UndoSterge.h"

void UndoSterge::DoUndo() {
    repo.store(v);
}