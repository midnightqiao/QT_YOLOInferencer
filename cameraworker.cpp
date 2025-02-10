#include "cameraworker.h"
#include <QCameraInfo>
#include <QDebug>

QImage mat2QImage(const cv::Mat mat2);

CameraWorker::CameraWorker(int index):isRunning(false),index(index),inf("./mask_normal_palsy.onnx", cv::Size(640, 640), "./classes.txt", false)
{

}

void CameraWorker::setIndex(int index)
{
    this->index = index;
}

void CameraWorker::setVideoCaptureSlot(bool toRunning)
{
    isRunning = toRunning;

//    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
//    // 输出摄像头个数
//    qDebug() << "the number of cameras: " << cameras.count();
//    // 遍历并输出每个摄像头的描述
//    for (const QCameraInfo &cameraInfo : cameras) {
//        qDebug() << "description: " << cameraInfo.description();
//    }

    if(isRunning){
        cout<<"open func"<<endl;

        if(!capture.isOpened()){

            try {
                capture.open(index);
                if(!capture.isOpened()){
                    cout<<"camera can't open"<<endl;
                    return;
                }
            } catch (Exception e) {

            }

        }
        while(true){
            cout<<"running"<<endl;
            Mat frame;
            capture.read(frame);
////            inf.runInference(frame);

            inf.predict(frame);
//            // Inference starts here...
//            std::vector<Detection> output = inf.runInference(frame);

//            int detections = output.size();
//            std::cout << "Number of detections:" << detections << std::endl;

//            // feiyull
//            // 这里需要resize下，否则结果不对
//    //        cv::resize(frame, frame, cv::Size(640, 640));

//            for (int i = 0; i < detections; ++i)
//            {
//                Detection detection = output[i];

//                cv::Rect box = detection.box;
//                cv::Scalar color = detection.color;

//                // Detection box
//                cv::rectangle(frame, box, color, 2);

//                // Detection box text
//                std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
//                cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
//                cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

//                cv::rectangle(frame, textBox, color, cv::FILLED);
//                cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
//            }
//            cv::resize(frame, frame, cv::Size(640, 640));


            emit predictFinished(frame);

            cout<<"predict slot"<<endl;

            cout<<"predict signal"<<endl;
            if(isRunning == false){
                if(capture.isOpened()){
                    capture.release();
                    emit cameraHasClosed();
                    cout<<"camera release"<<endl;
                }
                break;
            }
            waitKey(10);

        }
    }/*else{
        cout<<"close func"<<endl;
//        while(true){
//            waitKey(1000);
//        }
        if(capture.isOpened()){
            capture.release();
            cout<<"摄像头释放"<<endl;
        }
//        waitKey(10000);
    }*/
}

void CameraWorker::setInferenceOnnx(QString onnxFile)
{
    this->inf.setOnnx(onnxFile);
}

void CameraWorker::setInferenceClasses(QString classFile)
{
    this->inf.setClasses(classFile);
}

