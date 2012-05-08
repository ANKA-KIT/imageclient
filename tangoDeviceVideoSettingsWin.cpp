/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

void VideoSettingsWin::initButtons(){
    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(100, 20, 91, 24));
    btOk = new QPushButton(centralWidget);
    btOk->setObjectName(QString::fromUtf8("btOk"));
    btOk->setGeometry(QRect(5, 20, 91, 24));
}

void VideoSettingsWin::initText(){
    btCancel->setText("Cancel");
    btOk->setText("Ok");
    lb->setText("Command:");
    tl->setText("90");
    fprintf(stderr, "in VideoSettingsWin constructor\n");
}

void VideoSettingsWin::initTextLine(){
    lb = new QLabel(centralWidget);
    lb->setObjectName(QString::fromUtf8("lb"));
    lb->setGeometry(QRect(5, 0, 71, 16));
    tl = new QLineEdit(centralWidget);
    tl->setObjectName(QString::fromUtf8("tl"));
    tl->setGeometry(QRect(90, 0, 180, 20));
}

VideoSettingsWin::VideoSettingsWin(MainWindow *main, int param){//, SubWindow* win){
    VideoSettingsWin *MainWind = this;
    parent = main;
    //window = win;
    centralWidget = new QWidget(MainWind);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(300, 50);
    this->move(100,100);

    initButtons();
    initTextLine();
    initText();

    switch(param){
        case BRIGHTNESS_SNAPSHOT:{
            this->setWindowTitle("Set Brigthness Snapshot");
            lb->setText("BRIGHTNESS");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeBrightnessSnapshot()));

        }
        break;
        case CONTRAST_SNAPSHOT:{
            this->setWindowTitle("Set Contrast Snapshot");
            lb->setText("CONTRAST");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeContrastSnapshot()));
        }
        break;
        case GAMMA_SNAPSHOT:{
            this->setWindowTitle("Set Gamma Snapshot");
            lb->setText("GAMMA");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeGammaSnapshot()));
        }
        break;
        case ROTATION_SNAPSHOT:{
            lb->setText("ROTATION");
            this->setWindowTitle("Set Rotation Snapshot");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(rotateImg()));

        }
        break;
        case SCALE_SNAPSHOT:{
            lb->setText("SCALE");
            this->setWindowTitle("Set Scale Snapshot");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeScaleSnapshot()));
        }
        break;

        case BRIGHTNESS_REALTIME:{
            this->setWindowTitle("Set Brigthness Realtime");
            lb->setText("BRIGHTNESS");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeBrightnessRealtime()));

        }
        break;
        case CONTRAST_REALTIME:{
            this->setWindowTitle("Set Contrast Realtime");
            lb->setText("CONTRAST");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeContrastRealtime()));
        }
        break;
        case GAMMA_REALTIME:{
            this->setWindowTitle("Set Gamma Realtime");
            lb->setText("GAMMA");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeGammaRealtime()));
        }
        break;
        case ROTATION_REALTIME:{
            lb->setText("ROTATION");
            this->setWindowTitle("Set Rotation Realtime");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeRotationRealtime()));

        }
        break;
        case SCALE_REALTIME:{
            lb->setText("SCALE");
            this->setWindowTitle("Set Scale Realtime");
            QObject::connect(btOk,SIGNAL(clicked()), parent,SLOT(changeScaleRealtime()));
        }
        break;
            default: break;
    }
    QObject::connect(btCancel,SIGNAL(clicked()), parent,SLOT(cancelVSettingWin()));
}

VideoSettingsWin::~VideoSettingsWin(){
    delete lb;
    delete tl;
    delete btCancel;
    delete btOk;
    fprintf(stderr, "in VideoSettingsWin destructor\n");
}

//on Cancel click
void MainWindow::cancelVSettingWin(){
    vSetting->close();
    delete vSetting;
    vSetting = NULL;
}
