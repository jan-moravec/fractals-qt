#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include"library/fractal.h"

class WorkThread: public QThread
{
    Q_OBJECT

public:
    WorkThread(Fractal *frac = nullptr);
    void setFractal(Fractal *frac) {
        fractal = frac;
    }

signals:
    void finishedSignal();

private:
    Fractal *fractal = nullptr;
    void run() override;
};

#endif // WORKTHREAD_H
