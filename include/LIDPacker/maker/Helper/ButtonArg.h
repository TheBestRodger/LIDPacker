#pragma once
/*!
********************************************************
*	@file ButtonArg.h
*	@author Dmitry
*	@date  08/12/2022
*	@brief 
**********************************************************
*/

#include <QPushButton>
/*!******************************************
*
*	@brief 
*	@author Dmitry
*	@version 1.0
*	@date   08.12.2022
*
**************************************************/
namespace lid
{
	class ButtonArg : public QPushButton
	{
		Q_OBJECT
	public:
		ButtonArg(QWidget* pwgt = 0);
		~ButtonArg();
		int pos_as_btn;
		int pos_as_arg;
		bool clicked_f;
	};
}
