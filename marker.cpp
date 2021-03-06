#include "marker.h"
#include <QtWidgets>
#include <QDebug>
#include <cstdlib>
Marker::Marker(int row)
{
    setFlags(ItemIsSelectable|ItemIsMovable);
    setAcceptHoverEvents(true);
    setZValue(10);
    radius=20.0;
    innerRadius=10.0;
    this->color=this->idToColor(row);
}

QRectF Marker::boundingRect() const
{
    return QRectF(-radius-1,-radius-1,radius*2+3,radius*2+3);

}

QPainterPath Marker::shape() const
{
    QPainterPath path;
    path.addEllipse(-radius,-radius,radius*2+1,radius*2+1);
    return path;
}

void Marker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /*widget*/)
{
    QColor penColor=this->color;

    if(option->state & QStyle::State_Selected)
        //penColor=penColor.lighter();
        penColor=penColor.darker(400);
    if(option->state & QStyle::State_MouseOver)
        penColor=penColor.darker(200);

    QPainterPath circle;
    circle.addEllipse(-radius,-radius,radius*2+1,radius*2+1);
    circle.addEllipse(-innerRadius,-innerRadius,innerRadius*2+1,innerRadius*2+1);
    circle.setFillRule(Qt::OddEvenFill);

    painter->save();
    painter->setBrush(penColor);
    painter->setPen(Qt::blue);
    painter->drawPath(circle);
    painter->drawLine(-innerRadius,0,innerRadius,0);
    painter->drawLine(0,-innerRadius,0,innerRadius);
    painter->restore();
}

QColor Marker::idToColor(int id)
{
    int magicNum=(id*11)%36;
    QColor c=QColor::fromHsv(magicNum/36.*360,255,255);
    return c;
}



