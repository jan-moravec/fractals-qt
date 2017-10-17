#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QDebug>

#include "library/palette.h"
#include "library/mandelbrot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalLayout->setStretch(0, 1);
    ui->paintButton->setMinimumWidth(250);

    ui->widthSpinBox->setValue(800);
    ui->heightSpinBox->setValue(600);
    ui->iterationSpinBox->setValue(50);

    palette = new Palette;
    mandelbrot = new Mandelbrot;

    for (int i = 0; i < palette->getCount(); ++i) {
        ui->paletteComboBox->addItem(QString(palette->getPalette(i).name.c_str()));
    }

    connect(ui->paintWidget, PaintWidget::zoomMouseSignal, this, MainWindow::zoomChangedSlot);
    mandelbrot->setProgressFunction(std::bind( &MainWindow::updateProgress, this, std::placeholders::_1 ));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete palette;
    delete rgb;
}

void MainWindow::paintFractal(void)
{
    ui->statusBar->showMessage("Painting ", 3000);

    int w = ui->widthSpinBox->value();
    int h = ui->heightSpinBox->value();
    mandelbrot->setSize(w, h);
    mandelbrot->setIterations(ui->iterationSpinBox->value());
    mandelbrot->calculate();
    delete rgb;
    rgb = new uint8_t[w * h * 3];
    mandelbrot->fillRgb(rgb, palette->getCurrent());
    ui->paintWidget->setImage(rgb, w, h);
    ui->paintWidget->update();
}

void MainWindow::on_paintButton_clicked()
{
    qDebug() << "MainWindow::on_paintButton_clicked(): Painting";
    paintFractal();
}

void MainWindow::on_paletteComboBox_currentIndexChanged(int index)
{
    palette->setCurrent(index);
}

void MainWindow::on_ZommXSpinBox_valueChanged(int)
{
    ui->paintWidget->drawZoom(ui->ZommXSpinBox->value(), ui->ZoomYSpinBox->value(), ui->ZoomScaleDoubleSpinBox->value());
}

void MainWindow::on_ZoomYSpinBox_valueChanged(int)
{
    ui->paintWidget->drawZoom(ui->ZommXSpinBox->value(), ui->ZoomYSpinBox->value(), ui->ZoomScaleDoubleSpinBox->value());
}

void MainWindow::on_ZoomScaleDoubleSpinBox_valueChanged(double)
{
    ui->paintWidget->drawZoom(ui->ZommXSpinBox->value(), ui->ZoomYSpinBox->value(), ui->ZoomScaleDoubleSpinBox->value());
}

void MainWindow::on_zoomInPushButton_clicked()
{
    mandelbrot->zoomIn(ui->ZommXSpinBox->value(), ui->ZoomYSpinBox->value(), ui->ZoomScaleDoubleSpinBox->value());
    paintFractal();
}

void MainWindow::on_zoomOutPushButton_clicked()
{
    mandelbrot->zoomOut();
    paintFractal();
}

void MainWindow::zoomChangedSlot(int x, int y, double scale)
{
    ui->ZommXSpinBox->setValue(x);
    ui->ZoomYSpinBox->setValue(y);
    ui->ZoomScaleDoubleSpinBox->setValue(scale);
}

void MainWindow::updateProgress(double progress)
{
    ui->statusBar->showMessage("Painting " + QString::number(int(progress)) + "%", 3000);
}
