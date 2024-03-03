#ifndef CHARTVIEW_H
#define CHARTVIEW_H
/*!
********************************************************
*	@file ChartView.h
*	@author Dmitry
*	@date   31.01.2023
*	@brief описапния сцены для графика
**********************************************************
*/
#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>
#include <QtGui/QMouseEvent>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
/*!***********************************************
*
*   @brief Класс ChartView
*   Класс унаслежованный от QChartView для переопределения сцены
*   с возможностьми приближения сцены и отдаления кнопками на мыши и стрелки на клавиатуре
*   @author Dmitry
*   @version 1.0
*	@date   31.01.2023
*
****************************************************/
class ChartView : public QChartView
{
    Q_OBJECT
public:
    ChartView(QWidget* parent = 0);
    void getXY(qreal _x, qreal _y);
protected:
    bool viewportEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    bool m_isTouching;
    qreal x;
    qreal y;
    bool f;
public slots:

};

#endif