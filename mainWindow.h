#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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
    void zoomChangedSlot(int x, int y, double scale);
    void updateProgressSlot();

    void on_paintButton_clicked();
    void on_paletteComboBox_currentIndexChanged(int index);
    void on_ZommXSpinBox_valueChanged(int arg1);
    void on_ZoomYSpinBox_valueChanged(int arg1);
    void on_ZoomScaleDoubleSpinBox_valueChanged(double arg1);
    void on_zoomInPushButton_clicked();
    void on_zoomOutPushButton_clicked();

private:
    Ui::MainWindow *ui;
    uint8_t *rgb;
    Palette *palette;
    Fractal *mandelbrot;
    QTimer progressTimer;

    void calculateFractal(void);
    void paintFractal(void);
    void updateProgress(double progress);
    void disableAll(void);
    void enableAll(void);
};

#endif // MAINWINDOW_H
