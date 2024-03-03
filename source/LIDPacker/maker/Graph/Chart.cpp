/*!
********************************************************
*	@file Chart.cpp
*	@author QT and Kalikin D.M.
*	@date   31.01.2023
*	@brief реализация обозначения класса для построения графиков
**********************************************************
*/
#include "LIDPacker/maker/Graph/Chart.h"


Chart::Chart(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
}

Chart::~Chart()
{

}

bool Chart::sceneEvent(QEvent* event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QChart::event(event);
}

bool Chart::gestureEvent(QGestureEvent* event)
{
    
    if (QGesture* gesture = event->gesture(Qt::PanGesture)) {
        QPanGesture* pan = static_cast<QPanGesture*>(gesture);
        QChart::scroll(-(pan->delta().x()), pan->delta().y());
    }

    if (QGesture* gesture = event->gesture(Qt::PinchGesture)) {
        QPinchGesture* pinch = static_cast<QPinchGesture*>(gesture);
        if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged)
            QChart::zoom(pinch->scaleFactor());
    }

    return true;
}
