#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Biblioteca_GUI.h"

class BibliotecaCosUndoGUI : public QMainWindow
{
	Q_OBJECT

public:
	BibliotecaCosUndoGUI(QWidget* parent = Q_NULLPTR);

private:
	Ui::Biblioteca_GUIClass ui;
};


