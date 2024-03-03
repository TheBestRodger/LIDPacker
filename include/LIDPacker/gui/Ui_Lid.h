#pragma once
/*!
********************************************************
*   @file Ui_Lid.h
*   @author Dmitry
*   @date 11/02/2023
*   @brief Описание методов и подключаемые библиотеки
**********************************************************
*/
#ifndef Ui_Lid_H
#define Ui_Lid_H

#include <QMainWindow>
#include <QGridLayout>
#include <QMenuBar>
#include <QStatusBar>
QT_BEGIN_NAMESPACE
/*!***********************************************
*
*   @author Dmitry
*   @version 1.0
*   @date 11/02/2023
*   @brief Класс Ui_Lid графическое представление
*	главного окна где собираются другие приложения
****************************************************/
class Ui_Lid  : public QMainWindow
{
	Q_OBJECT
public:
	QWidget*	Analis;
	QWidget*	Redact;
	QWidget*	Viewer;
	QMenuBar*	menu;//!< menu - Главное меню
	QMenu*		mn_Open_file;//!< Под меню с файлом\сохранит\сохранить как\новый файл
	QMenu*		mn_last_Files;
	QMenu*		mn_Mode;
	QMenu*		mn_INFO;
	QStatusBar* statusbar;
	/*! \brief Кнопки меню и подменю которые делают действия*/
	QAction*	action_mn_View;
	QAction*	action_mn_Redact;
	QAction*	action_mn_Analis;
	/*! \brief Кнопки меню и подменю которые делают действия*/
	QAction*	action_mn_Save;
	QAction*	action_mn_Save_As;
	QAction*	action_mn_Open;
	QAction*	action_mn_New_File;
	QAction*	action_clear_last_Files;
	QAction*	action_mn_Exit;
	/*! \brief Кнопки главного меню*/
	QAction*	action_mn_Restore;
	QAction*	action_mn_Settings;
	QAction*	action_mn_INFO_about_LID;
	QAction*	action_mn_INFO_about_QT;

	void setupUi(QMainWindow* MainWind);
private:
	void retranslateUi(QMainWindow* MainWind);
};
namespace Ui {
	class ULid : public Ui_Lid {};
}
QT_END_NAMESPACE
#endif // TRANSZHQULY_H