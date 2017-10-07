#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "library/fractal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_paintButton_clicked();

    void on_paletteComboBox_currentIndexChanged(int index);

private:
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    uint8_t *rgb;
    Palette *palette;
    Fractal *mandelbrot;
};

#endif // MAINWINDOW_H
