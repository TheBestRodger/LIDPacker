#pragma once

/*!
********************************************************
*	@file callout.h
*	@author Dmitry
*	@date   31.01.2023
*	@brief обявления класса для подсказок по графику
**********************************************************
*/
#ifndef CALLOUT_H
#define CALLOUT_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QFont>
#include <QtGui/QPainter>
#include <QtGui/QFontMetrics>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QMouseEvent>
#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
/*!***********************************************
*
*   @brief Класс Callout
*   Создает в графическом виде на графике позиции координат
*   @author Dmitry
*   @version 1.0
*	@date   31.01.2023
*
****************************************************/
class Callout : public QGraphicsItem
{
public:
    Callout(QChart* parent);
    /*
    * @brief получение позиций координат
    * @param text с определенным форматом QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y())
    */
    void setText(const QString& text);
    /*
    * @brief получение позиций для закрепления описания
    * @param QPointF point
    */
    void setAnchor(QPointF point);
    /*
    * @brief обновление геометрии при изменении осей
    */
    void updateGeometry();
    /*
    * @brief Рамка координат
    */
    QRectF boundingRect() const;
    /*
    * @brief Установление кооринат в рамке по позициям и их изменением при движении курсора
    */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    QString m_text;
    QRectF m_textRect;
    QRectF m_rect;
    QPointF m_anchor;
    QFont m_font;
    QChart* m_chart;
};

#endif // CALLOUT_H
