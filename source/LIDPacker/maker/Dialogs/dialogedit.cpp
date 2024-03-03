/*!
********************************************************
*	@file DialogEdit.cpp
*	@author Dmitry
*	@date Декабрь  08/12/2022
*	@brief Модуль содержит реализацию файла DialogEdit.h
**********************************************************
*/

#include "LIDPacker/maker/Dialogs/dialogedit.h"
DialogEdit::DialogEdit(const QString& txt)
{
	ui = new Ui::DialogEdit();
	ui->setupUi(this);
	ui->ln_desc_arg->setPlainText(txt);
	connect(ui->btn_ok, SIGNAL(clicked()), SLOT(accept()));
	connect(ui->btn_no, SIGNAL(clicked()), SLOT(reject()));
}
DialogEdit::~DialogEdit()
{
	delete ui;
}
const QString DialogEdit::get_desc() const
{
	return ui->ln_desc_arg->toPlainText();
}