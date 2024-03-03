#pragma once
/*!
********************************************************
*	@file Graph.h
*	@author Kalikin D.M.
*	@date   09/01/2023
*	@brief Работа с графиком и его отображение
**********************************************************
*/
#include "../gui/Ui_Graph.h"
#include "Brain/Arguments.h"
#include "Brain/Data.h"
#include "Graph/Chart.h"
#include "Helper/TextLineEdit.h"
#include "Graph/callout.h"

#include <science/math/interpolation/interpolator.hpp>

#include <QGraphicsView>
#include <QStandardItemModel>
#include <QValueAxis>

/*!***********************************************
*
*   @brief Класс Graph
*   Реализует работу графиков по данным из Data
*   @author Kalikin D.M.
*   @version 2.0
*   @date   30/08/2023
*
****************************************************/
namespace lid
{
class Graph : public QGraphicsView
{
	Q_OBJECT

public:

	Graph(QWidget* parent = nullptr);
	~Graph();

	void set_path(const char* path);
	const QString get_path() const;
private:
	/* @brief Получение данных из интерполяции. */
	void							ConvertDataFromInterpol(science::Interpolator&);

	/* @brief  Коннекты всех кнопок кот. инициализировались в граф. интерфейсе. */
	void							AllStaticConnects();

	/* @brief 	*/
	void							DrawNamesForOCX();

	/* @brief 	*/
	void							FormCoordinates();

	/* @brief 	*/
	void							MakeLinePoint(QVector<int> &, const QString & name);

	/* @brief 	*/
	QColor							MakeLine(const QVector<sreal_t> &, const QString& name);

	/* @brief 	*/
	void							ClearTxt();

	/* @brief 	*/
	const sreal_t					Max_list(const QVector<sreal_t> &);

	/* @brief 	*/
	const sreal_t					Min_list(const QVector<sreal_t> &);
public:
	void manager(int, QVector<int> _p);
	void R1(QVector<int>);
	void R2(QVector<int>);
	void R3(QVector<int>);
	void R4(QVector<int>);
	void R5(QVector<int>);
	void R6(QVector<int>);
	void R7(QVector<int>);

protected slots:
	void							showContextMenu(QPoint pos);
private slots:
	void							DrawArgsWithoutOCX(QListWidgetItem* item);
	void							DrawTableVals();
	void							ChooseAllArg();
	bool							DeleteView();
	void							DeleteLine();
	/* Callout */
	void							resizeEvent(QResizeEvent* event);
	void							mouseMoveEvent(QMouseEvent* event);
	void							keepCallout();
	void							tooltip(QPointF point, bool state);
	/**********/
	void							Print_JPEG();
	void							Print_PNG();
	void							Print_PDF();
	void							OnOffDots();
	void							OnOffLines();
	void							OnOffSpline();
	void							OnOffAnime();
	void							PosAlign();
	void							OptOCXY();
	void							Max_OCX();
	void							Min_OCX();
	void							Max_OCY();
	void							Min_OCY();
	void							updateViewOCXmax(qreal);
	void							updateViewOCXmin(qreal);
	void							updateViewOCYmax(qreal);
	void							updateViewOCYmin(qreal);
private:
	/** \brief	*/
	bool dots;

	/** \brief	*/
	bool lines;

	/** \brief	*/
	bool splines;

	/** \brief	*/
	bool anime;

	/** \brief	*/
	int  align;

	/** \brief	*/
	double Max_X;

	/** \brief	*/
	double Min_X;

	/** \brief	*/
	double Max_Y;

	/** \brief	*/
	double Min_Y;

	/** \brief	*/
	QByteArray path;

	/** \brief	*/
	int pos_of_ocx;

	/** \brief	*/
	int count_lines;

	/** \brief	*/
	QHash<int, QVector<int>> AllCoordinates;

	/** \brief  Аргументы находящиеся в дереве. */
	std::shared_ptr<idArguments>	Args;

	/** \brief  Остальные данные об интерполяции.  */
	std::shared_ptr<Data>			data;

	/** \brief	*/
	Chart* chart;

	/** \brief	*/
	QValueAxis* axisX;

	/** \brief	*/
	QValueAxis* axisY;

	/** \brief	*/
	Ui::UGraph* ui;

	/** \brief	*/
	QWidget* SrollAreaWidget;

	/** \brief	*/
	QGridLayout* grid_args;

	/** \brief	*/
	QGraphicsSimpleTextItem* m_coordX;

	/** \brief	*/
	QGraphicsSimpleTextItem* m_coordY;

	/** \brief	*/
	Callout* m_tooltip;

	/** \brief	*/
	QList<Callout*> m_callouts;
	
	/** \brief	*/
	QStandardItemModel* TreeModel;
};

inline void Graph::AllStaticConnects()
{
	QObject::connect(ui->list_vals_args, &QListWidget::itemClicked, this, &Graph::DrawArgsWithoutOCX);
	QObject::connect(ui->tree_tbl_val, &QTreeView::customContextMenuRequested, this, &Graph::showContextMenu);

	QObject::connect(ui->btn_choose,		SIGNAL(clicked()),	 this, SLOT(DrawTableVals()));
	QObject::connect(ui->act_del,			SIGNAL(triggered()), this, SLOT(DeleteLine()));

	QObject::connect(ui->act_delete_view,	SIGNAL(triggered()), this, SLOT(DeleteView()));
	QObject::connect(ui->act_align,			SIGNAL(triggered()), this, SLOT(PosAlign()));
	QObject::connect(ui->act_anime,			SIGNAL(triggered()), this, SLOT(OnOffAnime()));
	QObject::connect(ui->act_OCXY,			SIGNAL(triggered()), this, SLOT(OptOCXY()));

	QObject::connect(ui->act_opt_dots,		SIGNAL(triggered()), this, SLOT(OnOffDots()));
	QObject::connect(ui->act_opt_lines,		SIGNAL(triggered()), this, SLOT(OnOffLines()));
	QObject::connect(ui->act_opt_splines,	SIGNAL(triggered()), this, SLOT(OnOffSpline()));

	QObject::connect(ui->act_Save_As_JPEG,	SIGNAL(triggered()), this, SLOT(Print_JPEG()));
	QObject::connect(ui->act_Save_As_PNG,	SIGNAL(triggered()), this, SLOT(Print_PNG()));
	QObject::connect(ui->act_Save_As_PDF,	SIGNAL(triggered()), this, SLOT(Print_PDF()));

	QObject::connect(ui->SpinBox_X_dwn,
		static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &Graph::Min_OCX);
	QObject::connect(ui->SpinBox_X_top,
		static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &Graph::Max_OCX);
	QObject::connect(ui->SpinBox_Y_dwn,
		static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &Graph::Min_OCY);
	QObject::connect(ui->SpinBox_Y_top,
		static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &Graph::Max_OCY);
}
ID_INLINE const QString Graph::get_path() const
{
	return path;
}
}
