#include "paintWidget.h"
#include <QPainter>
#include <QDebug>

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

    if (image->isNull()) {
        return;
    }

    QImage imScaled = image->scaled(this->size(), Qt::KeepAspectRatio);

    int offsetX = 0, offsetY = 0;
    if (imScaled.width() < this->width()) {
        offsetX = (this->width() - imScaled.width()) / 2;
    }
    if (imScaled.height() < this->height()) {
        offsetY = (this->height() - imScaled.height()) / 2;
    }

    QPainter painter(this);
    painter.drawImage(offsetX, offsetY, imScaled);
    QWidget::paintEvent(event);
}

void PaintWidget::setImage(uint8_t *bufferRgb, int width, int height)
{
    QMutexLocker locker(&paintMutex);

    delete image;
    image = new QImage(bufferRgb, width, height, QImage::Format_RGB888);
}
