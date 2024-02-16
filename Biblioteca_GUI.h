#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Biblioteca_GUI.h"

class Biblioteca_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Biblioteca_GUI(QWidget *parent = nullptr);
    ~Biblioteca_GUI();

private:
    Ui::Biblioteca_GUIClass ui;
};
