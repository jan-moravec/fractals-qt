#include "paintWidget.h"
#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent), image(new QImage)
{
}

PaintWidget::~PaintWidget()
{
    QMutexLocker locker(&paintMutex);
    delete image;
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QMutexLocker locker(&paintMutex);

    QPainter painter(this);
    painter.drawImage(0, 0, image->scaled(this->size(), Qt::KeepAspectRatio));
    QWidget::paintEvent(event);
}

void PaintWidget::setImage(uint8_t *bufferRgb, int width, int height)
{
    QMutexLocker locker(&paintMutex);

    delete image;
    image = new QImage(bufferRgb, width, height, QImage::Format_RGB888);
}
