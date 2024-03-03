#pragma once
/*!
********************************************************
*	@file DialogEdit.h
*	@author Dmitry
*	@date Декабрь  08/12/2022
*	@brief Модуль содержит подключаемые файлы и приватные переменный для интерфейса и методы
**********************************************************
*/
#ifndef DESIGNERPNDZNE_H
#define DESIGNERPNDZNE_H

#include "LIDPacker/maker/stylesdefine.h"
#include "LIDPacker/maker/predefine.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QTextCodec>
/*!*******************************
*
*	@brief Класс DialogEdit
*	Возможность редактирования
*   Также название аргументов
*	@author Dmitry
*	@version 1.0
*	@date Декабрь  08.12.2022
*
***********************************/
QT_BEGIN_NAMESPACE
class UiDialogEdit : public QDialog
{
public:
    QGridLayout* gridLayout;
    QVBoxLayout* V_lay;
    QPlainTextEdit* ln_desc_arg;
    QHBoxLayout* H_lay;
    QPushButton* btn_ok;
    QPushButton* btn_no;

    void setupUi(QDialog* Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        V_lay = new QVBoxLayout();
        V_lay->setObjectName(QString::fromUtf8("V_lay"));
        ln_desc_arg = new QPlainTextEdit(Dialog);
        ln_desc_arg->setObjectName(QString::fromUtf8("ln_desc_arg"));

        V_lay->addWidget(ln_desc_arg);

        H_lay = new QHBoxLayout();
        H_lay->setObjectName(QString::fromUtf8("H_lay"));
        btn_ok = new QPushButton(Dialog);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));

        H_lay->addWidget(btn_ok);

        btn_no = new QPushButton(Dialog);
        btn_no->setObjectName(QString::fromUtf8("btn_no"));

        H_lay->addWidget(btn_no);


        V_lay->addLayout(H_lay);


        gridLayout->addLayout(V_lay, 0, 0, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog* Dialog)
    {
        QTextCodec* codec = QTextCodec::codecForName(CODEC);
        QString str = codec->toUnicode("Описание аргумента");
        Dialog->setWindowTitle(str);
        Dialog->setFont(QFont(SHRIFT));
        str = codec->toUnicode("Изменить");
        btn_ok->setFont(QFont(SHRIFT, mFON));
        btn_ok->setText(str);
        str = codec->toUnicode("Отмена");
        btn_no->setFont(QFont(SHRIFT, mFON));
        btn_no->setText(str);
    } // retranslateUi
};
namespace Ui {
    class DialogEdit : public UiDialogEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERPNDZNE_H