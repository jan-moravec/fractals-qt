#include "workThread.h"
#include <QDebug>

WorkThread::WorkThread(Fractal *frac)
{
    fractal = frac;
}

void WorkThread::run()
{
    if (fractal != nullptr) {
        fractal->calculate();
    }

    qDebug() << "WorkThread::run(): Finished";
    emit finishedSignal();
}
