#include "photoworker.h"
#include <QFile>

PhotoWorker::PhotoWorker(QObject *parent) : QObject(parent),inf("./best.onnx", cv::Size(640, 640), "classes.txt", false)
{

}

void PhotoWorker::beginPhotoPredictSlot(QString name)
{
    filename = name;
    QFile file(filename);
    if(!file.exists()){
        cout<<"file not exists"<<endl;
        return;
    }
    cout<<"beggggggg read"<<endl;
    Mat mat = imread(filename.toStdString());
    cout<<"beggggggg read okkkkkkkkk"<<endl;

    if(mat.empty()){
        cout<<"eeeeeeeeeeeeeeeeeeeeeeee"<<endl;
        return;
    }
    Mat output = inf.predict(mat);
    emit predictFinished(output);
}
