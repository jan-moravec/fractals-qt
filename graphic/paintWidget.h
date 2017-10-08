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
    void drawZoom(int x, int y, double scale);

private:
    QImage *image = nullptr;
    QRect *zoomRect = nullptr;
    QMutex paintMutex;
    virtual void paintEvent(QPaintEvent *event);
};

#endif // PAINTWIDGET_H
