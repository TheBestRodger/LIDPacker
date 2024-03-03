#pragma once
/*!
********************************************************
*	@file TextLineEdit.h
*	@author Dmitry
*	@date  08/12/2022
*	@brief 
**********************************************************
*/

#include <QLineEdit>
#include <QMouseEvent>
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
	class TextLineEdit : public QLineEdit
	{
		Q_OBJECT
	public:
		TextLineEdit(QWidget* pwgt = 0);
		~TextLineEdit();
		int pos_arg;
		int pos;
		bool f;
		void clear_draw();
		void make_draw();
	protected:
		void mousePressEvent(QMouseEvent* event);
	};
}
