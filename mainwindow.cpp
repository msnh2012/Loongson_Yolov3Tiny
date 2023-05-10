#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

#include <QPixmap>
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->image1->setPixmap(QPixmap(imagePath));
    ui->image2->setPixmap(QPixmap(imagePath));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    try {
        msnhnet.buildNetFromMsnhNet("/home/msnh/models/yolov3_tiny/yolov3_tiny.msnhnet");
        msnhnet.loadWeightsFromMsnhBin("/home/msnh/models/yolov3_tiny/yolov3_tiny.msnhbin");
        Msnhnet::IO::readVectorStr(labels,"/home/msnh/Msnhnet/labels/coco.names","\n");

        QMessageBox::information(this,"提示","初始化网络成功");

    } catch (const Msnhnet::exception& ex) {
        QMessageBox::warning(this,"警告","初始化网络失败！"+QString::fromStdString(ex.what()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    const QString path = QFileDialog::getOpenFileName(this,"图片","","jpg(*.jpg)");

    if(path.isEmpty())
        return;

    imagePath = path;
    ui->image1->setPixmap(QPixmap(imagePath));
    ui->image2->setPixmap(QPixmap(imagePath));
}

QImage cvMatToQImage(const cv::Mat& mat)
{
    if(mat.type() == CV_8UC3)
    {
        const uchar* ptrSrc = mat.data;
        QImage image(ptrSrc,mat.cols, mat.rows,mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else
    {
        return {};
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    try
    {
        const Msnhnet::Point2I inSize = msnhnet.getInputSize();
        cv::Mat org = cv::imread(imagePath.toStdString());
        std::vector<float> img = Msnhnet::OpencvUtil::getPaddingZeroF32C3(imagePath.toStdString(), cv::Size(inSize.x,inSize.y));
        std::vector<std::vector<Msnhnet::YoloBox>> result = msnhnet.runYolo(img);
        Msnhnet::OpencvUtil::drawYoloBox(org,labels,result,inSize);

        ui->image2->setPixmap(QPixmap::fromImage(cvMatToQImage(org)));

    } catch (const Msnhnet::exception& ex) {
        QMessageBox::warning(this,"警告","推理失败！"+QString::fromStdString(ex.what()));
    }

}
