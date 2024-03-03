/*!
********************************************************
*   @file Ui_Lid.cpp
*   @author Kalikin D.M.
*   @date 11/02/2023
*   @brief Реализация графических элементов
**********************************************************
*/
#include "LIDPacker/gui/Ui_Lid.h"
#include "LIDPacker/maker/stylesdefine.h"

#include <QTextCodec>
#include <LIDPacker/maker/predefine.h>
void Ui_Lid::setupUi(QMainWindow* MainWind) {

	MainWind->setStyleSheet(style_app);
	menu			= new QMenuBar(MainWind);//!< menu - Главное меню
	menu->setFont(QFont(SHRIFT, mFON));
	mn_Open_file	= new QMenu(menu);//!< Под меню с файлом\сохранит\сохранить как\новый файл\выход
	mn_INFO			= new QMenu(menu);
	statusbar		= new QStatusBar();

	/*! \brief Кнопки меню и подменю которые делают действия*/
	action_mn_Save				= new QAction(mn_Open_file);
	action_mn_Save_As			= new QAction(mn_Open_file);
	action_mn_Open				= new QAction(mn_Open_file);
	action_mn_New_File			= new QAction(mn_Open_file);
	action_clear_last_Files		= new QAction(mn_Open_file);
	mn_last_Files				= new QMenu(mn_Open_file);
	action_mn_Exit				= new QAction(mn_Open_file);
	/*! \brief Кнопки главного меню*/
	mn_Mode						= new QMenu(menu);
	action_mn_View				= new QAction(mn_Mode);
	action_mn_Redact			= new QAction(mn_Mode);
	action_mn_Analis			= new QAction(mn_Mode);
	///////
	action_mn_Restore			= new QAction(menu);
	action_mn_Settings			= new QAction(menu);
	///////
	action_mn_INFO_about_LID	= new QAction(mn_INFO);
	action_mn_INFO_about_QT		= new QAction(mn_INFO);
	////////////////////////////////////////////////
	mn_last_Files->addAction(action_clear_last_Files);
	mn_last_Files->addSeparator();
	//!Добавления в подменю
	mn_Open_file->addAction(action_mn_Open);
	mn_Open_file->addAction(action_mn_New_File);
	mn_Open_file->addSeparator();
	mn_Open_file->addAction(action_mn_Save);
	mn_Open_file->addAction(action_mn_Save_As);
	mn_Open_file->addSeparator();
	mn_Open_file->addMenu(mn_last_Files);
	mn_Open_file->addSeparator();
	mn_Open_file->addAction(action_mn_Exit);
	///! Режимы
	mn_Mode->addAction(action_mn_View);
	mn_Mode->addAction(action_mn_Redact);
	mn_Mode->addAction(action_mn_Analis);
	//!Добавление в меню
	menu->addMenu(mn_Open_file);	
	menu->addMenu(mn_Mode);
	menu->addAction(action_mn_Restore);
	menu->addAction(action_mn_Settings);
	menu->addMenu(mn_INFO);
	mn_INFO->addAction(action_mn_INFO_about_LID);
	mn_INFO->addAction(action_mn_INFO_about_QT);
	//////////////////////////////////////////////////

	retranslateUi(MainWind);
	MainWind->setMenuBar(menu);
	MainWind->setStatusBar(statusbar);
	MainWind->resize(800, 800);
	MainWind->move(500, 900);
}
void Ui_Lid::retranslateUi(QMainWindow* MainWind) {
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(ANSI));

    /*******************************************/
	QString translate = QString::fromLocal8Bit("Файл");
    mn_Open_file->setTitle(translate);
    mn_Open_file->setFont(QFont(SHRIFT, mFON));
	const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    translate = QString::fromLocal8Bit("Сохранить");
    action_mn_Save->setText(translate);
	action_mn_Save->setIcon(saveIcon);
	action_mn_Save->setShortcuts(QKeySequence::Save);

	const QIcon saveasIcon = QIcon::fromTheme("document-save-as", QIcon(":/images/paste.png"));
    translate = QString::fromLocal8Bit("Сохранить как");
    action_mn_Save_As->setText(translate);
	action_mn_Save_As->setIcon(saveasIcon);
	action_mn_Save_As->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));

    translate = QString::fromLocal8Bit("Открыть файл");
	const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    action_mn_Open->setText(translate);
	action_mn_Open->setIcon(openIcon);
	action_mn_Open->setShortcuts(QKeySequence::Open);

    translate = QString::fromLocal8Bit("Новый файл");
	const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    action_mn_New_File->setText(translate);
	action_mn_New_File->setIcon(newIcon);
	action_mn_New_File->setShortcuts(QKeySequence::New);

	translate = QString::fromLocal8Bit("Очистить");
	action_clear_last_Files->setText(translate);

	translate = QString::fromLocal8Bit("Последние файлы");
	mn_last_Files->setTitle(translate);

	translate = QString::fromLocal8Bit("Выход");
	action_mn_Exit->setText(translate);
	action_mn_Exit->setShortcuts(QKeySequence::Close);
	/*************************************************/
	translate = QString::fromLocal8Bit("Режимы");
	mn_Mode->setTitle(translate);	
	mn_Mode->setFont(QFont(SHRIFT, mFON));
	translate = QString::fromLocal8Bit("Просмотр");
	action_mn_View->setText(translate);
	//action_mn_View->setShortcut(QKeySequence(Qt::ALT + Qt::Key_Q));
	action_mn_View->setVisible(false);
	translate = QString::fromLocal8Bit("Редактирование");
	action_mn_Redact->setText(translate);
	action_mn_Redact->setShortcut(QKeySequence(Qt::ALT + Qt::Key_W));
	translate = QString::fromLocal8Bit("Анализ");
	action_mn_Analis->setText(translate);
	action_mn_Analis->setShortcut(QKeySequence(Qt::ALT + Qt::Key_E));
	/****************************************************/
    translate = QString::fromLocal8Bit("Восстановить");
    action_mn_Restore->setText(translate);
	action_mn_Restore->setShortcut(QKeySequence(Qt::ALT + Qt::Key_2));

	action_mn_Restore->setStatusTip("To restore - > Alt + 2");
	action_mn_Restore->setVisible(false);

	translate = QString::fromLocal8Bit("Настройки");
	action_mn_Settings->setText(translate);
	action_mn_Settings->setVisible(false);

    translate = QString::fromLocal8Bit("О программе");
    mn_INFO->setTitle(translate);
	mn_INFO->setFont(QFont(SHRIFT, mFON));

	translate = QString::fromLocal8Bit("Функционал");
	action_mn_INFO_about_LID->setText(translate);

	translate = QString::fromLocal8Bit("Используемое ПО");
	action_mn_INFO_about_QT->setText(translate);

}
