#pragma once
/*!
********************************************************
*	@file Dialogdelete.h
*	@author Dmitry
*	@date Декабрь  08/12/2022
*	@brief Модуль содержит подключаемые файлы и приватные переменный для интерфейса и методы
**********************************************************
*/
#include <QDialog>
#include <QTableView>

/*!*******************************
*
*	@brief Класс Dialogdelete
*	Диалог удаления
*	@author Dmitry
*	@version 1.0
*	@date Декабрь  08.12.2022
*
*************************************/
#ifndef UNTITLEDBXBYFZ_H
#define UNTITLEDBXBYFZ_H

#include <LIDPacker/maker/stylesdefine.h>
#include "LIDPacker/maker/predefine.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QTextCodec>

QT_BEGIN_NAMESPACE

class Ui_DialogDel
{
public:
    QGridLayout* gridLayout;
    QVBoxLayout* main_vert_lay;
    QComboBox* Args_box;
    QTableView* tabel_vals_arg;
    QHBoxLayout* hlay_btn;
    QPushButton* btn_ok;
    QPushButton* btn_no;

    void setupUi(QDialog* Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(755, 451);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        main_vert_lay = new QVBoxLayout();
        main_vert_lay->setObjectName(QString::fromUtf8("main_vert_lay"));
        Args_box = new QComboBox(Dialog);
        Args_box->setObjectName(QString::fromUtf8("Args_box"));

        main_vert_lay->addWidget(Args_box);

        tabel_vals_arg = new QTableView(Dialog);
        tabel_vals_arg->setObjectName(QString::fromUtf8("tabel_vals_arg"));
        tabel_vals_arg->setSelectionMode(QAbstractItemView::MultiSelection);
        main_vert_lay->addWidget(tabel_vals_arg);

        hlay_btn = new QHBoxLayout();
        hlay_btn->setObjectName(QString::fromUtf8("hlay_btn"));
        btn_ok = new QPushButton(Dialog);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));

        hlay_btn->addWidget(btn_ok);

        btn_no = new QPushButton(Dialog);
        btn_no->setObjectName(QString::fromUtf8("btn_no"));

        hlay_btn->addWidget(btn_no);


        main_vert_lay->addLayout(hlay_btn);


        gridLayout->addLayout(main_vert_lay, 0, 0, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog* Dialog)
    {
        QTextCodec* codec = QTextCodec::codecForName(CODEC);
        QString str = codec->toUnicode("Удаление значений");
        Dialog->setWindowTitle(str);
        Dialog->setFont(QFont(SHRIFT));
        str = codec->toUnicode("Удалить");
        btn_ok->setFont(QFont(SHRIFT, mFON));
        btn_ok->setText(str);
        str = codec->toUnicode("Отмена");
        btn_no->setFont(QFont(SHRIFT, mFON));
        btn_no->setText(str);
    } // retranslateUi

};

namespace Ui {
    class DialogDel : public Ui_DialogDel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UNTITLEDBXBYFZ_H
