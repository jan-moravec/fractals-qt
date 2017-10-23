#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QDebug>
#include <QFileDialog>

#include "library/palette.h"
#include "library/mandelbrot.h"
#include "library/workThread.h"

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

    ui->ZommXSpinBox->setEnabled(false);
    ui->zoomInPushButton->setEnabled(false);
    ui->zoomOutPushButton->setEnabled(false);
    ui->ZoomYSpinBox->setEnabled(false);
    ui->ZoomScaleDoubleSpinBox->setEnabled(false);
    ui->saveImageButton->setEnabled(false);

    palette = new Palette;
    mandelbrot = new Mandelbrot;

    for (int i = 0; i < palette->getCount(); ++i) {
        ui->paletteComboBox->addItem(QString(palette->getPalette(i).name.c_str()));
    }

    connect(&progressTimer, SIGNAL(timeout()), this, SLOT(updateProgressSlot()));
    connect(ui->paintWidget, SIGNAL(PaintWidget::zoomMouseSignal), this, SLOT(MainWindow::zoomChangedSlot));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete palette;
    delete rgb;
}

void MainWindow::disableAll(void)
{
    ui->heightSpinBox->setEnabled(false);
    ui->iterationSpinBox->setEnabled(false);
    ui->paintButton->setEnabled(false);
    ui->paletteComboBox->setEnabled(false);
    ui->widthSpinBox->setEnabled(false);
    ui->ZommXSpinBox->setEnabled(false);
    ui->zoomInPushButton->setEnabled(false);
    ui->zoomOutPushButton->setEnabled(false);
    ui->ZoomYSpinBox->setEnabled(false);
    ui->ZoomScaleDoubleSpinBox->setEnabled(false);
    ui->saveImageButton->setEnabled(false);
}

void MainWindow::enableAll(void)
{
    ui->heightSpinBox->setEnabled(true);
    ui->iterationSpinBox->setEnabled(true);
    ui->paintButton->setEnabled(true);
    ui->paletteComboBox->setEnabled(true);
    ui->widthSpinBox->setEnabled(true);
    ui->ZommXSpinBox->setEnabled(true);
    ui->zoomInPushButton->setEnabled(true);
    ui->zoomOutPushButton->setEnabled(true);
    ui->ZoomYSpinBox->setEnabled(true);
    ui->ZoomScaleDoubleSpinBox->setEnabled(true);
    ui->saveImageButton->setEnabled(true);
}

void MainWindow::calculateFractal(void)
{
    disableAll();

    int w = ui->widthSpinBox->value();
    int h = ui->heightSpinBox->value();
    mandelbrot->setSize(w, h);
    mandelbrot->setIterations(ui->iterationSpinBox->value());

    WorkThread *workThread = new WorkThread(mandelbrot);
    connect(workThread, WorkThread::finishedSignal, this, MainWindow::paintFractal);
    workThread->start();
    progressTimer.start(100);
}

void MainWindow::paintFractal(void)
{
    progressTimer.stop();
    ui->statusBar->showMessage("Finished", 3000);

    int w = ui->widthSpinBox->value();
    int h = ui->heightSpinBox->value();

    delete rgb;
    rgb = new uint8_t[w * h * 3];
    mandelbrot->fillRgb(rgb, palette->getCurrent());
    ui->paintWidget->setImage(rgb, w, h);
    ui->paintWidget->update();

    enableAll();
}

void MainWindow::on_paintButton_clicked()
{
    qDebug() << "MainWindow::on_paintButton_clicked(): Painting";
    calculateFractal();
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
    calculateFractal();
}

void MainWindow::on_zoomOutPushButton_clicked()
{
    mandelbrot->zoomOut();
    calculateFractal();
}

void MainWindow::zoomChangedSlot(int x, int y, double scale)
{
    ui->ZommXSpinBox->setValue(x);
    ui->ZoomYSpinBox->setValue(y);
    ui->ZoomScaleDoubleSpinBox->setValue(scale);
}

void MainWindow::updateProgressSlot()
{
    double progress = mandelbrot->getProgressPercent();
    updateProgress(progress);
}
void MainWindow::updateProgress(double progress)
{
    ui->statusBar->showMessage("Painting " + QString::number(int(progress)) + "%");
}

void MainWindow::on_saveImageButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Address Book"), "",
            tr("PNG Image (*.png);;JPEG Image (*.jpg);;BMP Image (*.bmp)"));
    ui->paintWidget->getImage()->save(fileName);
}
