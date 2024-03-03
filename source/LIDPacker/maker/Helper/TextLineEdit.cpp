/*!
********************************************************
*	@file TextLineEdit.cpp
*	@author Kalikin D.M.
*	@date Декабрь  08/12/2022
*	@brief Модуль содержит реализацию файла TextLineEdit.h
**********************************************************
*/

#include <LIDPacker/maker/Helper/TextLineEdit.h>
#include <LIDPacker/maker/stylesdefine.h>

#include <QRegExpValidator>

lid::TextLineEdit::TextLineEdit(QWidget* pwgt)
	: QLineEdit(pwgt)
{
	QRegExp rxp("[0-9 \\. -]+");
	setValidator(new QRegExpValidator(rxp, this));
	setFrame(true);
	f = false;
	pos_arg = pos = 0;
}
lid::TextLineEdit::~TextLineEdit()
{
}
void lid::TextLineEdit::clear_draw()
{
	this->setStyleSheet(style_app);
	f = false;
}
void lid::TextLineEdit::make_draw()
{
	this->setStyleSheet("background:rgb(184, 255, 180)");
	f = true;
}
void lid::TextLineEdit::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton)
	{
		if (f)
		{
			this->setStyleSheet(style_app);
			f = false;
		}
		else
		{
			this->setStyleSheet("background:rgb(184, 255, 180)");
			f = true;
		}
	}

}