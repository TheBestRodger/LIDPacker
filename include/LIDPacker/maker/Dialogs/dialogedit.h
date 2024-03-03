#pragma once
/*!
********************************************************
*	@file	DialogEdit.h
*	@author Dmitry
*	@date	08/12/2022
*	@brief	
**********************************************************
*/
#include <QDialog>
#include "LIDPacker/gui/Dialogs/UI_dialogedit.h"
/*!*******************************
*
*	@brief Класс DialogEdit
*	@author Dmitry
*	@version 1.0
*	@date 08/12/2022
*
***********************************/
class DialogEdit : public QDialog
{
	Ui::DialogEdit* ui;
public:
	DialogEdit(const QString& txt);
	~DialogEdit();
	const QString get_desc() const;
};
