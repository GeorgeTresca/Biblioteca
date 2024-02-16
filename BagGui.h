//
// Created by Andrei on 5/9/2023.
//

#ifndef ANDREI_BAGGUI_H
#define ANDREI_BAGGUI_H

#endif //ANDREI_BAGGUI_H
#include "Carte.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QLineEdit>
#include <QFormLayout>
#include "Biblioteca.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include "Repo.h"
#include "Validator.h"
#include "Observer.h"
#include "service_bag.h"
class BagGui :public QWidget, public Observer {
private:
    QListWidget* lst = new QListWidget;
    QVBoxLayout* main = new QVBoxLayout;
    service_cos& srv;
    void init()
    {
        this->setLayout(main);
        main->addWidget(lst);
        lst->unsetCursor();
    }

    void load_data()
    {
        lst->clear();
        for (const auto elem : srv.srv_get_all_bag())
        {
            auto item = new QListWidgetItem(QString::fromStdString(elem.getTitlu()));
            item->setData(Qt::UserRole, QString::fromStdString(elem.getAutor()));
            lst->addItem(item);
        }
    }


public:
    BagGui(service_cos& serv) :srv{ serv } {
        init();
        load_data();
    };


    void update() override {
        load_data();
    }

};