#pragma once
#ifndef DESIGNERMVREAJ_H
#define DESIGNERMVREAJ_H

#include <LIDPacker/maker/stylesdefine.h>
#include "LIDPacker/maker/predefine.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QTextCodec>


QT_BEGIN_NAMESPACE

class Ui_DialogAdd
{
public:
    QGridLayout* gridLayout;

    QVBoxLayout* main_vert_lay;

    QHBoxLayout* Hlay_amount;
    QHBoxLayout* hlay_btn;

    QComboBox* Args_box;

    QLabel* lbl_am;
    QLineEdit* ln_amount;

    QTableView* list_vals_arg;

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

        Hlay_amount = new QHBoxLayout();
        Hlay_amount->setObjectName(QString::fromUtf8("Hlay_amount"));
        lbl_am = new QLabel(Dialog);
        lbl_am->setObjectName(QString::fromUtf8("lbl_am"));
        QFont font;
        font.setPointSize(12);
        lbl_am->setFont(font);

        Hlay_amount->addWidget(lbl_am);

        ln_amount = new QLineEdit(Dialog);
        ln_amount->setObjectName(QString::fromUtf8("ln_amount"));

        Hlay_amount->addWidget(ln_amount);


        main_vert_lay->addLayout(Hlay_amount);

        list_vals_arg = new QTableView(Dialog);
        list_vals_arg->setObjectName(QString::fromUtf8("list_vals_arg"));

        main_vert_lay->addWidget(list_vals_arg);

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
        QString str = codec->toUnicode("Добавление значений");
        Dialog->setWindowTitle(str);
        Dialog->setFont(QFont(SHRIFT));
        str = codec->toUnicode("Добавить значений:");
        lbl_am->setText(str);
        str = codec->toUnicode("Добавить");
        btn_ok->setFont(QFont(SHRIFT, mFON));
        btn_ok->setText(str);
        str = codec->toUnicode("Отмена");
        btn_no->setFont(QFont(SHRIFT, mFON));
        btn_no->setText(str);
    } // retranslateUi

};

namespace Ui {
    class DialogAdd : public Ui_DialogAdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERMVREAJ_H
