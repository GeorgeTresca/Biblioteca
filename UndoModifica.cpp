#include "UndoModifica.h"

void UndoModifica::DoUndo() {
    repo.modifica_carte(v);
}