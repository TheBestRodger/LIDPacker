#pragma once
/*!
********************************************************
*   @file DialogPlain.h
*   @author Dmitry
*   @date 17/02/2023
*   @brief Описание классов и подключаемые библиотеки
**********************************************************
*/
#include <QDialog>
#include <LIDPacker/gui/Dialogs/UI_dialogplain.h>
#include <qstandarditemmodel.h>
#include <science/core/type.hpp>
/*!***********************************************
*
*   @brief Класс DialogPlain
*   @author Dmitry
*   @version 1.0
*   @date 17/02/2023
*   Показывает описание аргумена в режиме просмотр
****************************************************/
class DialogPlain : public QDialog
{
	Ui::DialogPl* ui;
	QStandardItemModel* Valmodel;
	QMap<int, QVector<sreal_t>> scales;
	QVector<int> pl;
public:
	//Dialogdelete(QStringList names, QMap<int, QVector<sreal_t>> args_vals);
	DialogPlain(QStringList names, QMap<int, QVector<sreal_t>> args_vals, int pos, QVector<int> _p);
	~DialogPlain();
	const int get_plain() const;
	const int get_pos() const;

private slots:
	void change_table_data(int index);
};
