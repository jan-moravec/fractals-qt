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

    mandelbrot = new Mandelbrot;
    mandelbrot->setSize(500, 500);
    rgb = new uint8_t[500 * 500 * 3];
    mandelbrot->calculate();
    mandelbrot->fillRgb(rgb);
    ui->paintWidget->setImage(rgb, 500, 500);
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
    ui->paintWidget->update();
}
