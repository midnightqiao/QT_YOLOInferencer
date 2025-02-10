#ifndef PHOTOWORKER_H
#define PHOTOWORKER_H

#include <QObject>
#include "inference.h"
#include <opencv.hpp>

using namespace std;
using namespace cv;

class PhotoWorker : public QObject
{
    Q_OBJECT
public:
    explicit PhotoWorker(QObject *parent = nullptr);

    void setInferenceOnnx(QString onnxFile);
    void setInferenceClasses(QString classFile);
private:
    Inference inf;
    QString filename;

public slots:
    void beginPhotoPredictSlot(QString name);
signals:
    void predictFinished(Mat& mat);

};

#endif // PHOTOWORKER_H
