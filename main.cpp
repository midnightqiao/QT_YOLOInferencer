#include "widget.h"

#include <QApplication>
#include <opencv.hpp>
#include <QImage>
#include <vector>
#include <string>
#include "inference.h"
#include <QMetaType>
#include <QTextCodec>

using namespace std;
using namespace cv;
using namespace cv::dnn;

QImage mat2QImage(Mat mat2);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat>("Mat&");

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//	QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
//	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());


//    cv::Mat mat2 = cv::imread("C:/Users/ysp/Desktop/8.jpg");
//    Mat mat;
////    resize(mat2,mat,Size(mat2.cols/4,mat2.rows/4));
//    resize(mat2,mat,Size(549,784));
//    imshow("hello",mat);
//    cout<<"mat:"<<mat.cols<<" "<<mat.rows<<endl;
//    cout<<"mat.size:"<<mat.size()<<endl;
//    cout<<"mat.channels:"<<mat.channels()<<endl;
//    cout<<"mat[0,0]:"<<mat.at<int>(90000)<<endl;
//    cout<<"mat.dims:"<<mat.dims<<endl;
//    cout<<"mat.total:"<<mat.total()<<endl;
//    cout<<"mat.elemSize:"<<mat.elemSize()<<endl;
//    cout<<"mat.step:"<<mat.step<<endl;
//    cout<<"mat.type"<<mat.type()<<endl;



//    Mat image = imread("C:/Users/ysp/Desktop/yolov8_data/wangyibo2.jpg");
//    imshow("src",image);
//    cout<<"image:"<<image.cols<<" "<<image.rows<<endl;
//    cout<<"image.size:"<<image.size()<<endl;
//    cout<<"image.channels:"<<image.channels()<<endl;
//    cout<<"image[0,0]:"<<image.at<int>(90000)<<endl;
//    cout<<"image.dims:"<<image.dims<<endl;
//    cout<<"image.total:"<<image.total()<<endl;
//    cout<<"image.elemSize:"<<image.elemSize()<<endl;
//    cout<<"image.step:"<<image.step<<endl;
//    cout<<"image.type"<<image.type()<<endl;

//    Mat mat3 = mat.reshape(1,784);
//    cout<<"mat:"<<mat3.cols<<" "<<mat3.rows<<endl;
//    cout<<"mat.size:"<<mat3.size()<<endl;
//    cout<<"mat.channels:"<<mat3.channels()<<endl;
//    cout<<"mat[0,0]:"<<mat3.at<int>(90000)<<endl;
//    cout<<"mat.dims:"<<mat3.dims<<endl;
//    cout<<"mat.total:"<<mat3.total()<<endl;
//    cout<<"mat.elemSize:"<<mat3.elemSize()<<endl;
//    cout<<"mat.step:"<<mat3.step<<endl;
//    cout<<"mat.type"<<mat3.type()<<endl;
//    imshow("2222",mat3);

//    Net net = readNetFromONNX("C:/Users/ysp/Desktop/yolov8Src/ultralytics-main/runs/detect/train15/weights/best.onnx");
//    if(net.empty()){
//        cout<<"make sure net is correct"<<endl;
//    }

//    Mat blob = blobFromImage(mat,1.0,Size(640,640),Scalar(),true,false);
//    cout<<"blob:"<<blob.cols<<" "<<blob.rows<<endl;
//    cout<<"blob:"<<blob.size()<<endl;

////    imshow("blob",blob);


//    net.setInput(blob);
//    Mat res = net.forward();

////    vector<string> layerNames = net.getLayerNames();
////    for(string name : layerNames){
////        int ID = net.getLayerId(name);
////        Ptr<Layer> layer = net.getLayer(ID);
////        cout<<"layerID:"<<ID<<"\tlayerName:"<<name<<endl<<"layerType:"<<layer->type<<endl;
////    }

//    cout<<"res.data:"<<(float*)res.data<<endl;
//    float* data = (float*)res.data;
//    cout<<"data[0]"<<(int)(data[0]*640)<<endl;
//    cout<<"data[1]"<<(int)(data[1]*640)<<endl;
//    cout<<"data[2]"<<(int)(data[2]*640)<<endl;
//    cout<<"data[3]"<<(int)(data[3]*640)<<endl;
//    cout<<"data[4]"<<(int)(data[4]*640)<<endl;
//    cout<<"data[5]"<<(int)(data[5]*640)<<endl;

////    rectangle(mat,cv::Point(data[0]))
//    float b = res.at<float>(1);
//    cout<<"b"<<b<<endl;

//    cout<<"res:"<<res.cols<<" "<<res.rows<<endl;
//    cout<<"res.size:"<<res.size()<<endl;
//    cout<<"res.channels:"<<res.channels()<<endl;
////    cout<<"res[0,0]:"<<res.at<int>(90000)<<endl;
//    cout<<"res.dims:"<<res.dims<<endl;
////    imshow("net result",res);





//    bool runOnGPU = false;

//    // 1. 设置你的onnx模型
//    // Note that in this example the classes are hard-coded and 'classes.txt' is a place holder.
//    Inference inf("C:/Users/ysp/Desktop/yolov8Src/ultralytics-main/runs/detect/train15/weights/best.onnx", cv::Size(640, 640), "classes.txt", runOnGPU); // classes.txt 可以缺失

//    // 2. 设置你的输入图片
//    std::vector<std::string> imageNames;
//    imageNames.push_back("C:/Users/ysp/Desktop/yolov8_data/luhan.jpg");
//    //imageNames.push_back("zidane.jpg");

//    for (int i = 0; i < imageNames.size(); ++i)
//    {
//        cv::Mat frame = cv::imread(imageNames[i]);



//        // Inference starts here...
//        std::vector<Detection> output = inf.runInference(frame);

//        int detections = output.size();
//        std::cout << "Number of detections:" << detections << std::endl;

//        // feiyull
//        // 这里需要resize下，否则结果不对
////        cv::resize(frame, frame, cv::Size(640, 640));

//        for (int i = 0; i < detections; ++i)
//        {
//            Detection detection = output[i];

//            cv::Rect box = detection.box;
//            cv::Scalar color = detection.color;

//            // Detection box
//            cv::rectangle(frame, box, color, 2);

//            // Detection box text
//            std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
//            cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
//            cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

//            cv::rectangle(frame, textBox, color, cv::FILLED);
//            cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
//        }
//        cv::resize(frame, frame, cv::Size(640, 640));
//        cv::imshow("Inference", frame);
//        cv::waitKey(0);
//        cv::destroyAllWindows();
//    }


    Widget w;
    w.show();


    return a.exec();
}

//QImage mat2QImage(Mat mat2){
//    Mat mat;
//    cvtColor(mat2,mat,COLOR_BGR2RGB);
//    uchar* data = mat.data;
//    switch(mat.type()){
//        case CV_8UC1:{
//            QImage img(data,mat.cols,mat.rows,mat.step,QImage::Format::Format_Grayscale8);
//            return img;
//        }
//        case CV_8UC3:{
//            QImage img(data,mat.cols,mat.rows,mat.step,QImage::Format::Format_RGB32);
//            return img;
//        }
//        case CV_8UC4:{
//            QImage img(data,mat.cols,mat.rows,mat.step,QImage::Format::Format_ARGB32);
//            return img;
//        }
//        default:{
//            return QImage();
//        }
//    }
//}
