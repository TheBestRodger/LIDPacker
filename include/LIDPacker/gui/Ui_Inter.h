#pragma once
/*!
********************************************************
*   @file Ui_Inter.h
*   @author Dmitry
*   @date 11/02/2023
*   @brief Описание методов и подключаемые библиотеки
**********************************************************
*/

/*!***********************************************
*
*   @brief Класс Ui_Inter
*   @author Dmitry
*   @version 1.0
*   @date 11/02/2023
*
****************************************************/

#ifndef DESIGNEREEACXB_H
#define DESIGNEREEACXB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QMenuBar>
#include <QTextCodec>
#include <LIDPacker/maker/stylesdefine.h>
#include <LIDPacker/maker/predefine.h>

QT_BEGIN_NAMESPACE

class Ui_Inter
{
public:
    QGridLayout* gridLayout;
    QVBoxLayout* V_lay;
    QTableWidget* table_inter;
    QMenuBar* menu;
    QAction* act_interpolate;
    QAction* act_dump_results;
    ~Ui_Inter()
    {
        delete act_interpolate;
        delete act_dump_results;
    }
    void setupUi(QWidget* InterUI)
    {
        gridLayout          = new QGridLayout(InterUI);
        table_inter         = new QTableWidget(InterUI);
        V_lay               = new QVBoxLayout();
        menu                = new QMenuBar();
        act_interpolate     = new QAction();
        act_dump_results    = new QAction();



        menu->addAction(act_interpolate);
        menu->addAction(act_dump_results);
        V_lay->addWidget(menu);
        //V_lay->addLayout(horizontalLayout);
        V_lay->addWidget(table_inter);


        gridLayout->addLayout(V_lay, 0, 0, 1, 1);
        InterUI->setLayout(gridLayout);
        retranslateUi(InterUI);

    } // setupUi

    void retranslateUi(QWidget* InterUI)
    {
        InterUI->setWindowTitle(QCoreApplication::translate("InterUI", "Interpolation", nullptr));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName(ANSI));

        /*******************************************/
        QString translate = QString::fromLocal8Bit("Интерполировать");
        act_interpolate->setText(translate);
        act_interpolate->setFont(QFont(SHRIFT, mFON));

        translate = QString::fromLocal8Bit("Выгрузить результаты");
        act_dump_results->setText(translate);
        act_dump_results->setFont(QFont(SHRIFT, mFON));
    } // retranslateUi

};

namespace Ui {
    class InterUI : public Ui_Inter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNEREEACXB_H
