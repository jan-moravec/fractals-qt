#include "paintWidget.h"
#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::black);
    QWidget::paintEvent(event);
}
