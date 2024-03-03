#pragma once
/*!
********************************************************
*	@file Dialogdelete.h
*	@author Dmitry
*	@date Декабрь  08/12/2022
*	@brief Модуль содержит подключаемые файлы и приватные переменный для интерфейса и методы
**********************************************************
*/
#include <QStandardItemModel>
#include "LIDPacker/gui/Dialogs/UI_dialogdelete.h"
#include <science/core/type.hpp>
/*!*******************************
*
*	@brief Класс Dialogdelete
*	Диалог удаления
*	@author Dmitry
*	@version 1.0
*	@date Декабрь  08.12.2022
*  
*
*
*************************************/
class Dialogdelete : public QDialog
{
	Ui::DialogDel* ui;
	QStandardItemModel* Valmodel;
	QMap<int, QVector<sreal_t>> scales;
public:
	//Dialogdelete(QStringList names, QMap<int, QVector<sreal_t>> args_vals);
	Dialogdelete(QStringList names, QMap<int, QVector<sreal_t>> args_vals, int pos);
	const QVector<int> get_deleted_pos();
	const int get_pos() const;
private slots:
	void change_table_data(int index);
};
