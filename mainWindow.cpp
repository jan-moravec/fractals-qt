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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete palette;
    delete rgb;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
}

void MainWindow::on_paintButton_clicked()
{
    qDebug() << "MainWindow::on_paintButton_clicked(): Painting";
    ui->statusBar->showMessage("Painting", 3000);

    int w = ui->widthSpinBox->value();
    int h = ui->heightSpinBox->value();
    mandelbrot->setSize(w, h);
    mandelbrot->setIterations(ui->iterationSpinBox->value());
    mandelbrot->addZoom(ui->ZommXSpinBox->value(), ui->ZoomYSpinBox->value(), ui->ZoomScaleDoubleSpinBox->value());
    mandelbrot->calculate();
    delete rgb;
    rgb = new uint8_t[w * h * 3];
    mandelbrot->fillRgb(rgb, palette->getCurrent());
    ui->paintWidget->setImage(rgb, w, h);
    ui->paintWidget->update();
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
