#pragma once
#ifndef Ui_Graph_H
#define Ui_Graph_H

/*!
********************************************************
*	@file Ui_Graph.h
*	@author Dmitry
*	@date   18.01.2023
*	@brief Графика
**********************************************************
*/
#include "LIDPacker/maker/Graph/ChartView.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QSplitter>
#include <QListWidget>
#include <qmenubar.h>
#include <QDoubleSpinBox>
QT_BEGIN_NAMESPACE
/*!***********************************************
*
*   @brief Класс Ui_Graph
*   Графическое представление
*   @author Dmitry
*   @version 1.0
*   @date   18.01.2023
*
****************************************************/
using namespace QtCharts;
class Ui_Graph  : public QWidget
{
public:
    QVBoxLayout* Main_Vlay;
    QVBoxLayout* VLay_3;
    QVBoxLayout* grd_central_lay;
    QLabel* lbl_table_val;
    QTreeView* tree_tbl_val;
    QVBoxLayout* Vlay_1;
    QLabel* lbl_ch_OCX;
    QListWidget* list_vals_args;
    QPushButton* btn_choose;
    QVBoxLayout* VLay_2;
    QLabel* lbl_val_args;
    QTableWidget* table_ch_values;
    ChartView* chartview;

    QWidget* verticalLayoutWidget;
    QVBoxLayout* verticalLayout;
    QHBoxLayout* lay_X;
    QLabel* lbl_X;
    QDoubleSpinBox* SpinBox_X_dwn;
    QDoubleSpinBox* SpinBox_X_top;
    QHBoxLayout* lay_Y;
    QLabel* lbl_Y;
    QDoubleSpinBox* SpinBox_Y_dwn;
    QDoubleSpinBox* SpinBox_Y_top;

    QMenuBar*   menu;
    QAction*    act_align;
    QAction*    act_OCXY;
    QAction*    act_delete_view;

    QMenu*      Export_Pic;
    QAction*    act_Save_As_PNG;
    QAction*    act_Save_As_JPEG;
    QAction*    act_Save_As_PDF;

    QMenu*      menu_options;
    QAction*    act_opt_dots;
    QAction*    act_opt_lines;
    QAction*    act_opt_splines;
    QAction*    act_anime;

    QSplitter* spl_H;
    QSplitter* spl_V;

    QWidget* tmp;
    QWidget* wgt_05;
    QWidget* wgt_1;
    QWidget* wgt_2;
    QWidget* wgt_3;

    QMenu* del_menu;
    QAction* act_del;

    QScrollArea* ScrollArea;
	
	void setupUi(QWidget* graphics);	
private:
	void retranslateUi(QWidget* graphics);
};

namespace Ui {
	class UGraph : public Ui_Graph {};
}
QT_END_NAMESPACE

#endif // DESIGNERFXCYTE_H