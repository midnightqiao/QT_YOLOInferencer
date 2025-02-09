#include "widget.h"
#include "./ui_widget.h"
#include <opencv.hpp>
#include <QImage>
#include <QFileDialog>
#include <QAction>
#include <QDateTime>
#include <QCameraInfo>
#include <QDebug>


using namespace cv;
using namespace std;



Widget::Widget(QWidget *parent):
     QWidget(parent),worker(new CameraWorker()),worker2(new PhotoWorker())
    ,saveImage(new QAction("save Image to")),saveDebugInfo(new QAction("save debug info to"))
   ,dealedMat(Mat())
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : cameras) {
        ui->cameraList->addItem(cameraInfo.description());
    }


    setWindowTitle(QStringLiteral("人员检测"));
    worker->moveToThread(thread);
    thread->start();
    worker2->moveToThread(thread2);
    thread2->start();

    QObject::connect(this,&Widget::setVideoCaptureSignal,worker,&CameraWorker::setVideoCaptureSlot);
    QObject::connect(worker,&CameraWorker::predictFinished,this,&Widget::predictFinishedSlot);
    QObject::connect(worker,&CameraWorker::cameraHasClosed,this,&Widget::detectCameraClosed);
    QObject::connect(this,&Widget::beginPredictSignal,worker2,&PhotoWorker::beginPhotoPredictSlot);
    QObject::connect(worker2,&PhotoWorker::predictFinished,this,&Widget::predictFinishedSlot);
    QObject::connect(saveImage,&QAction::triggered,this,&Widget::saveImageSlot);
    QObject::connect(saveDebugInfo,&QAction::triggered,this,&Widget::saveDebugInfoSlot);

    ui->label->setFixedSize(640,640);
    ui->label_2->setFixedSize(640,640);
    ui->label->setScaledContents(true);
    ui->label_2->setScaledContents(true);


    QFile file(":/images/images/8.jpg");
    if(!file.open(QFile::ReadOnly)){
        cout<<"resource file 8.jpg not exist"<<endl;
        return;
    }
    QByteArray buffer = file.readAll();
    cv::Mat mat2 = cv::imdecode(vector<uchar>(buffer.begin(),buffer.end()),cv::IMREAD_COLOR);

    cv::Mat mat;
    if(mat2.empty()){
        cout<<"mat is empty"<<endl;
        return;
    }
    cv::resize(mat2,mat,Size(549,784));
    QImage img = mat2QImage(mat);
    if(img.isNull()){
        cout<<"img is null"<<endl;
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));

    imwrite("test.jpg",mat2);


    ui->toolButton->setIcon(QIcon(":/utility/utility/save.png"));
    ui->toolButton->setFixedSize(160,100);
    ui->toolButton->addAction(saveImage);
    ui->toolButton->addAction(saveDebugInfo);
    ui->textBrowser->setFixedHeight(300);

    ui->toolButton->setToolTip(QStringLiteral("保存..."));

    QString baseLetter="hello,world by ysp";
    this->appendDebugInfo(baseLetter);
    this->appendDebugInfo(baseLetter);


}

void Widget::run()
{
    cout<<"hello,world by ysp"<<endl;
    return;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::predictFinishedSlot(Mat& mat)
{
    QImage img = mat2QImage(mat);
    ui->label_2->setPixmap(QPixmap::fromImage(img));
    dealedMat = mat;
    cout<<"predict slot"<<endl;
}

void Widget::detectCameraClosed()
{
    if(filename.isEmpty()){
        return;
    }
    emit beginPredictSignal(filename);
    filename.clear();
}


void Widget::on_pushButton_clicked()
{
//        Mat frame;
//        cap.open(0);
//        if(!cap.isOpened()){
//            cout<<"camera isn't open"<<endl;
//        }
//        cap.read(frame);
//        QImage img =  mat2QImage(frame);
//        ui->label->setPixmap(QPixmap::fromImage(img));
    this->worker->setIndex(ui->cameraList->currentIndex());
    emit setVideoCaptureSignal(status);
    status = !status;
    if(!status){
        ui->pushButton->setText(QString::fromLocal8Bit("关闭摄像头"));
    }else{
        ui->pushButton->setText(QString::fromLocal8Bit("打开摄像头"));
    }
}


QImage mat2QImage(const cv::Mat mat2){
    cv::Mat mat;
    cvtColor(mat2,mat,COLOR_BGR2RGB);
//    imshow("88",mat);
    uchar* data = mat.data;
//    cout<<"mat.data"<<mat.data<<endl;
//    cout<<"mat.step"<<mat.step<<endl;
//    cout<<"mat.type"<<mat.type()<<endl;
//    cout<<mat.cols<<" "<<mat.rows<<endl;
    switch(mat.type()){
        case CV_8UC1:{
//            cout<<"8uc1"<<endl;
            QImage img(data,(int)mat.cols,(int)mat.rows,(int)mat.step,QImage::Format_Grayscale8);
            return img;
        }
        case CV_8UC3:{
//        cout<<"8uc3"<<endl;
            QImage img(data,(int)mat.cols,(int)mat.rows,(int)mat.step,QImage::Format_RGB888);
            return img.copy();
        }
        case CV_8UC4:{
//            cout<<"8uc4"<<endl;
            QImage img(data,(int)mat.cols,(int)mat.rows,(int)mat.step,QImage::Format::Format_ARGB32);
            return img;
        }
        default:{
            cout<<"default"<<endl;
            return QImage();
        }
    }
}

void Widget::on_pushButton_2_clicked()
{

    this->filename = QFileDialog::getOpenFileName(this,"select one picture",QString(),tr("Imagessss (*.png *.jpg *.jpeg)"));
    if(this->filename.isEmpty()){
        this->appendDebugInfo("dont choos file");
        return;
    }
    this->appendDebugInfo("have chosen file,filename:"+this->filename);
//    cout<<filename.toStdString()<<endl;
//    QFile file(filename);
//    if(!file.exists()){
//        cout<<"file not exists"<<endl;
//        return;
//    }
    Mat t = imread(filename.toStdString());
    if(t.empty()){
//        cout<<"image isn't valid"<<endl;
        this->appendDebugInfo("Image Info can't be read,may be file is uncorrect");
        return;
    }

    ui->label->setPixmap(QPixmap::fromImage(QImage(filename)));

    if(!status){
        emit setVideoCaptureSignal(false);
        status = true;
        if(!status){
            ui->pushButton->setText(QString::fromLocal8Bit("关闭摄像头"));
        }else{
            ui->pushButton->setText(QString::fromLocal8Bit("打开摄像头"));
        }
    }else{
        emit beginPredictSignal(filename);
    }
}

void Widget::saveImageSlot()
{
    if(dealedMat.empty()){
//        ui->textBrowser->append(QStringLiteral("没有处理过的图片"));
        this->appendDebugInfo(QStringLiteral("没有处理过的图片"));
        return;
    }
    QString filename = QFileDialog::getSaveFileName(this,"save image to",QString(),"images (*.jpg *.png *.jpeg)");

    if(filename.isEmpty()){
//        ui->textBrowser->append(QStringLiteral("没有选择保存的文件地址"));
        this->appendDebugInfo(QStringLiteral("没有选择保存的文件地址"));
        return;
    }
//    ui->textBrowser->append(QString("image saved ")+filename);
    this->appendDebugInfo(QString("image saved ")+filename);
    imwrite(filename.toStdString(),dealedMat);
}

void Widget::saveDebugInfoSlot()
{
    QString filename = QFileDialog::getSaveFileName(this,"save Debug Info to",QString(),"(*.txt)");
    if(filename.isEmpty()){
//        ui->textBrowser->append(QStringLiteral("没有选择保存的文件地址"));
        this->appendDebugInfo(QStringLiteral("没有选择保存的文件地址"));
        return;
    }

    QFile file(filename);
    if(!file.open(QFile::WriteOnly)){
//        ui->textBrowser->append(QStringLiteral("Fail open Debug Info"));
        this->appendDebugInfo(QStringLiteral("Fail open Debug Info"));
        return;
    }
//    ui->textBrowser->append(QString("Debug Info saved ")+filename);
    this->appendDebugInfo(QString("Debug Info saved ")+filename);
    file.write(ui->textBrowser->toPlainText().toStdString().c_str());
    file.close();
}

void Widget::appendDebugInfo(QString info){
    QString timeStr = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz:]\t");
    ui->textBrowser->append(timeStr+info);
}



void Widget::on_fresh_clicked()
{
    ui->cameraList->clear();
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : cameras) {
        ui->cameraList->addItem(cameraInfo.description());
    }

}
