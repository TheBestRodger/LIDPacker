#ifndef CHART_H
#define CHART_H
/*!
********************************************************
*	@file Chart.h
*	@author Dmitry
*	@date   31.01.2023
*	@brief обозначение класса для построения графиков
**********************************************************
*/
#include <QtCharts/QChart>
#include <QtWidgets/QGesture>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>

QT_BEGIN_NAMESPACE
class QGestureEvent;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
/*!***********************************************
*
*   @brief Класс Chart
*   Класс унаслежованный от QChart для переопределения графика и иветов сролла
*   @author Dmitry
*   @version 1.0
*	@date   31.01.2023
*
****************************************************/
class Chart : public QChart
{
public:
    explicit Chart(QGraphicsItem* parent = 0, Qt::WindowFlags wFlags = 0);
    ~Chart();

protected:
    bool sceneEvent(QEvent* event);

private:
    bool gestureEvent(QGestureEvent* event);

private:

};

#endif // CHART_H