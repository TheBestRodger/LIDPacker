/*!
********************************************************
*	@file ButtonArg.cpp
*	@author Kalikin D.M.
*	@date Декабрь  08/12/2022
*	@brief Модуль содержит реализацию файла ButtonArg.h
**********************************************************
*/

#include <LIDPacker/maker/Helper/ButtonArg.h>

lid::ButtonArg::ButtonArg(QWidget* pwgt)
	: QPushButton(pwgt)
	, pos_as_arg(0)
	, pos_as_btn(0)
	, clicked_f(false)
{
}
lid::ButtonArg::~ButtonArg()
{
}
