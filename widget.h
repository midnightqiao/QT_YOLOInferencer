#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "inference.h"
#include "opencv.hpp"
#include <QThread>
#include "cameraworker.h"
#include "photoworker.h"

using namespace std;
using namespace cv;

QImage mat2QImage(const cv::Mat mat2);

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    CameraWorker* worker;
    PhotoWorker* worker2;

public:
    Widget(QWidget *parent = nullptr);
    void run();
    ~Widget();
public slots:
    void predictFinishedSlot(Mat& mat);
//    void predictFinishedSlot(Mat& mat);
    void detectCameraClosed(void);

signals:
    void setVideoCaptureSignal(bool toRunning);
    void beginPredictSignal(QString name);
private:
    QAction* saveImage;
    QAction* saveDebugInfo;
    Mat dealedMat;
    Ui::Widget *ui;
    QThread* thread = new QThread();
    QThread* thread2 = new QThread();
    bool status = true;
    QString filename;

    QString onnxFile;
    QString classFile;
    void appendDebugInfo(QString info);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void saveImageSlot();
    void saveDebugInfoSlot();
    void on_fresh_clicked();
    void on_fileChooseBtn_clicked();
};
#endif // WIDGET_H
