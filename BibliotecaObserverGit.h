#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Biblioteca_GuiGit.h"

class BibliotecaObserverGit : public QMainWindow
{
	Q_OBJECT

public:
	BibliotecaObserverGit(QWidget* parent = Q_NULLPTR);

private:
	Ui::BibliotecaGui ui;
};
