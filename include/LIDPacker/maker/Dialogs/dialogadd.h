#pragma once
/*!
********************************************************
*	@file DialogAdd.h
*	@author Dmitry
*	@date Декабрь  08/12/2022
*	@brief 
**********************************************************
*/
#include <QStandardItemModel>
#include "LIDPacker/gui/Dialogs/UI_dialogadd.h"
#include <science/core/type.hpp>
/*!************************************
*
*	@brief Класс DialogAdd
*	Диалог добавления
*	@author Dmitry
*	@version 1.0
*	@date Декабрь  08.12.2022
*
****************************************/
class DialogAdd : public QDialog
{	
	Q_OBJECT
	/*
	* DEBUG
	* Можно ли из одного виджета передавать упарвление на другой
	* Использовать этот класс для редактировании таблицы
	* DEBUG
	*/
	Ui::DialogAdd* ui;
	QStandardItemModel* Valmodel;
	QMap<int, QVector<sreal_t>> scales;
public:
	DialogAdd(QStringList names, QMap<int, QVector<sreal_t>> scale, int pos);
	~DialogAdd();

	const int get_pos() const;
	const QVector<sreal_t> get_args() const;

private slots:
	void add_columns_tabel(const QString& text);
	void find_sames();
};
