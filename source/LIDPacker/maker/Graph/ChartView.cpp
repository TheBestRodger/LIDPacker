/*!
********************************************************
*	@file ChartView.cpp
*	@author QT and Kalikin D.M.
*	@date   31.01.2023
*	@brief Реализация файла ChartView.h
**********************************************************
*/


#include "LIDPacker/maker/Graph/ChartView.h"
#include <QGesture>
#include <QDebug> 
ChartView::ChartView(QWidget* parent) : QChartView(),
    m_isTouching(false)
{

    setRubberBand(QChartView::RectangleRubberBand);

}

bool ChartView::viewportEvent(QEvent* event)
{
    if (event->type() == QEvent::TouchBegin) {
        m_isTouching = true;
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    bool f;
    try {
        f = QChartView::viewportEvent(event);
    }
    catch (std::exception ex) {
        qWarning() << ex.what() << QDate::currentDate();
    }
    return f;//крашит из-за скорости обработки - не успевает обработать экран, и еще из-а чего то, может быть из-за потери области и ее видимости
}

void ChartView::mousePressEvent(QMouseEvent* event)
{
    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);

}
void ChartView::getXY(qreal _x, qreal _y) 
{
    x = _x;
    y = _y;
    f = true;
}
void ChartView::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isTouching)
        return;
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_isTouching)
        m_isTouching = false;
    //chart()->setAnimationOptions(QChart::GridAxisAnimations);
    //chart()->setAnimationOptions(QChart::SeriesAnimations);// Вот тут выключить обе анимации помеять на NoAnimation

    QChartView::mouseReleaseEvent(event);
}
void ChartView::wheelEvent(QWheelEvent* event) {

    QPoint p = event->angleDelta();
    QPointF xy = event->position();
    if (p.y() > 0) {
        chart()->zoomIn();
    }
    else {
        chart()->zoomOut();
    }
    
    QChartView::wheelEvent(event);
}
void ChartView::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
