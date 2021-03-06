#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMutex>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();
    void setImage(uint8_t *bufferRgb, int width, int height);
    const QImage *getImage(void) const { return image; }
    void drawZoom(int x, int y, double scale);
    void setZoomVisible(bool visible) { isZoomVisible = visible; update(); }

signals:
    void zoomMouseSignal(int x, int y, double scale);

private:
    QImage *image = nullptr;
    QRect *zoomRect = nullptr;
    bool isZoomVisible = false;
    QRect *zoomRectMouse = nullptr;
    QMutex paintMutex;
    QRect recalculateZoomPaint(const QRect &zoomFractal);
    QRect recalculateZoomFractal(const QRect &zoomImage);

    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
};

#endif // PAINTWIDGET_H
