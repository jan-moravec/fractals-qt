#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);

private:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // PAINTWIDGET_H
