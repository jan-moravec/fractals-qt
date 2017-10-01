#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QDebug>

#include "library/mandelbrot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalLayout->setStretch(0, 1);
    ui->paintButton->setMinimumWidth(150);

    ui->widthSpinBox->setValue(600);
    ui->heightSpinBox->setValue(600);
    ui->iterationSpinBox->setValue(50);

    mandelbrot = new Mandelbrot;
}

MainWindow::~MainWindow()
{
    delete ui;
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
    delete rgb;
    rgb = new uint8_t[w * h * 3];
    mandelbrot->calculate();
    mandelbrot->fillRgb(rgb);
    ui->paintWidget->setImage(rgb, w, h);
    ui->paintWidget->update();
}
