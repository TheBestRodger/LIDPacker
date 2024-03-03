#pragma once
/*!
********************************************************
*   @file Lid.h
*   @author Kalikin D.M.
*   @date 09/02/2023
*   @brief Описание методов и подключаемые библиотеки к главному окну
**********************************************************
*/
#include "LIDPacker/gui/Ui_Lid.h"
#include "LIDPacker/maker/Redaction.h"
#include "LIDPacker/maker/Graph.h"

#include <QMainWindow>

template<typename T>
ID_INLINE bool if_in_qvec(const QVector<T>& _vec, const T& _p)
{
	for (int i = 0; i < _vec.size(); ++i)
		if (_vec[i] == _p)
			return false;
	return true;
}

/*!***********************************************
*
*   @brief Класс Lid содержит три режима для работы с данными, настройки, меню и работа с файлом
*   реализует инструменты для графического интерфейса 
*   @author Kalikin D.M.
*   @version 1.0
*   @date 09.02.2023
*
****************************************************/
namespace lid {
class Lid : public QMainWindow
{
	Q_OBJECT
public:
	explicit	Lid(QWidget* parent = nullptr);
	~Lid();
protected:
	void		dragEnterEvent(QDragEnterEvent* event)  override;
	void		dropEvent(QDropEvent* event)			override;
	void		closeEvent(QCloseEvent* event)			override;
private:

	void		ReadSettings();
	void		WriteSettings();
	bool		MaybeSave();
	void		AllConnects();

	QMenuBar*	MakeFastMenu();

private slots:
	void		Mod_Redaction();
	void		Mod_View();
	void		Mod_Analis();
	/* В РАЗРАБОТКЕ */
	void		App_Interpol();

	bool		OpenFile();
	bool		ResetFile();
	bool		SaveFile();
	bool		SaveAsFile();
	void		NewFile();
	void		Exit();
	void		OpenLastFile();
	void		ClearLastFiles();

	void		INFOQT();
	void		INFOLID();
private:
	/** \brief Графический интерфейс */
	Ui::ULid* ui;

	/** \brief Путь до файла */
	QString path;

	/** \brief Переменная для установки режима работы и возвращение к нему после окончания работы */
	int last_mod;// 0 - V, 1 - R, 2 - A

	/** \brief Объект мода редактирования */
	Redaction* Red;

	/** \brief */
	Graph* Anls;

	QVector<QString> Vec_To_Files;
};
inline void Lid::AllConnects()
{
	QObject::connect(ui->action_mn_Open,			SIGNAL(triggered()), SLOT(OpenFile()));
	QObject::connect(ui->action_mn_Restore,			SIGNAL(triggered()), SLOT(ResetFile()));
	QObject::connect(ui->action_mn_Save,			SIGNAL(triggered()), SLOT(SaveFile()));
	QObject::connect(ui->action_mn_Save_As,			SIGNAL(triggered()), SLOT(SaveAsFile()));
	QObject::connect(ui->action_mn_View,			SIGNAL(triggered()), SLOT(Mod_View()));
	QObject::connect(ui->action_mn_Redact,			SIGNAL(triggered()), SLOT(Mod_Redaction()));
	QObject::connect(ui->action_mn_Analis,			SIGNAL(triggered()), SLOT(Mod_Analis()));
	QObject::connect(ui->action_mn_New_File,		SIGNAL(triggered()), SLOT(NewFile()));
	QObject::connect(ui->action_mn_Exit,			SIGNAL(triggered()), SLOT(Exit()));
	QObject::connect(ui->action_clear_last_Files,	SIGNAL(triggered()), SLOT(ClearLastFiles()));
	QObject::connect(ui->action_mn_INFO_about_QT,	SIGNAL(triggered()), SLOT(INFOQT()));
	QObject::connect(ui->action_mn_INFO_about_LID,	SIGNAL(triggered()), SLOT(INFOLID()));
}
}
