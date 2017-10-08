#include "paintWidget.h"
#include <QPainter>
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent), image(new QImage), zoomRect(new QRect)
{
}

PaintWidget::~PaintWidget()
{
    QMutexLocker locker(&paintMutex);
    delete image;
    delete zoomRect;
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QMutexLocker locker(&paintMutex);

    if (image->isNull()) {
        return;
    }

    QImage imScaled = image->scaled(this->size(), Qt::KeepAspectRatio);

    int offsetX = 0, offsetY = 0;
    double scale = (double)imScaled.width() / image->width();
    if (imScaled.width() < this->width()) {
        offsetX = (this->width() - imScaled.width()) / 2;
    }
    if (imScaled.height() < this->height()) {
        offsetY = (this->height() - imScaled.height()) / 2;
    }

    int x, y, w, h;
    x = zoomRect->x()*scale + offsetX;
    y = zoomRect->y()*scale + offsetY;
    w = zoomRect->width()*scale;
    h = zoomRect->height()*scale;

    /*rectZoom.setWidth(rectZoom.width()*scale);
    rectZoom.setHeight(rectZoom.height()*scale);
    rectZoom.setX(rectZoom.x()*scale);
    rectZoom.setY(rectZoom.y()*scale);*/
    //rectZoom.adjust(offsetX, offsetY, offsetX, offsetY);

    QRect rectZoom(x, y, w, h);

    QPainter painter(this);
    painter.drawImage(offsetX, offsetY, imScaled);
    painter.drawRect(rectZoom);
    QWidget::paintEvent(event);
}

void PaintWidget::setImage(uint8_t *bufferRgb, int width, int height)
{
    QMutexLocker locker(&paintMutex);

    delete image;
    image = new QImage(bufferRgb, width, height, QImage::Format_RGB888);
}

void PaintWidget::drawZoom(int x, int y, double scale)
{
    QMutexLocker locker(&paintMutex);

    if (image->isNull()) {
        return;
    }

    zoomRect->setRect(x, y, image->width()/scale, image->height()/scale);
    this->update();
}
