#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include <QObject>
#include <iostream>
#include "opencv.hpp"
#include "inference.h"
#include <QLabel>

using namespace std;
using namespace cv;

class CameraWorker:public QObject
{
    Q_OBJECT
public:
    CameraWorker(int index=0);
    void setIndex(int index);
public slots:
    void setVideoCaptureSlot(bool toRunning);

signals:
    void predictFinished(Mat& mat);
    void cameraHasClosed();

private:
    VideoCapture capture;
    Inference inf;
    int index;
    bool isRunning;
};

#endif // CAMERAWORKER_H
