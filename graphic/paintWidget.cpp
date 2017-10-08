#include "paintWidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent), image(new QImage), zoomRect(new QRect), zoomRectMouse(new QRect)
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
    if (imScaled.width() < this->width()) {
        offsetX = (this->width() - imScaled.width()) / 2;
    }
    if (imScaled.height() < this->height()) {
        offsetY = (this->height() - imScaled.height()) / 2;
    }

    /*int x, y, w, h;
    double scale = (double)imScaled.width() / image->width();
    x = zoomRect->x()*scale + offsetX;
    y = zoomRect->y()*scale + offsetY;
    w = zoomRect->width()*scale;
    h = zoomRect->height()*scale;*/

    QRect rectZoom = recalculateZoomPaint(*zoomRect);

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

QRect PaintWidget::recalculateZoomPaint(const QRect &zoomFractal)
{
    double scale = 1.0;
    double scaleX = (double)this->width() / image->width();
    double scaleY = (double)this->height() / image->height();
    if (scaleX < scaleY) {
        scale = scaleX;
    } else {
        scale = scaleY;
    }

    int offsetX = 0, offsetY = 0;
    if (image->width()*scale < this->width()) {
        offsetX = (this->width() - image->width()*scale) / 2;
    }
    if (image->height()*scale < this->height()) {
        offsetY = (this->height() - image->height()*scale) / 2;
    }

    int x, y, w, h;
    x = zoomFractal.x()*scale + offsetX;
    y = zoomFractal.y()*scale + offsetY;
    w = zoomFractal.width()*scale;
    h = zoomFractal.height()*scale;

    return QRect(x, y, w, h);
}

QRect PaintWidget::recalculateZoomFractal(const QRect &zoomImage)
{
    double scale = 1.0;
    double scaleX = (double)this->width() / image->width();
    double scaleY = (double)this->height() / image->height();
    if (scaleX < scaleY) {
        scale = scaleX;
    } else {
        scale = scaleY;
    }

    int offsetX = 0, offsetY = 0;
    if (image->width()*scale < this->width()) {
        offsetX = (this->width() - image->width()*scale) / 2;
    }
    if (image->height()*scale < this->height()) {
        offsetY = (this->height() - image->height()*scale) / 2;
    }

    int x, y, w, h;
    x = (zoomImage.x() - offsetX) / scale;
    y = (zoomImage.y() - offsetY) / scale;
    w = zoomImage.width()/scale;
    h = zoomImage.height()/scale;

    return QRect(x, y, w, h);
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (image->isNull()) {
        return;
    }

    *zoomRectMouse = QRect(event->pos(), event->pos());
    *zoomRect = recalculateZoomFractal(*zoomRectMouse);
    this->update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (image->isNull()) {
        return;
    }

    zoomRectMouse->setCoords(zoomRectMouse->x(), zoomRectMouse->y(), event->pos().x(), event->pos().y());
    *zoomRect = recalculateZoomFractal(*zoomRectMouse);
    this->update();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (image->isNull()) {
        return;
    }

    // Adjust ratio
    double scale = (double)image->width() / zoomRect->width();
    drawZoom(zoomRect->x(), zoomRect->y(), scale);
    emit zoomMouseSignal(zoomRect->x(), zoomRect->y(), scale);
}
