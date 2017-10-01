#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->horizontalLayout->setStretch(0, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
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
