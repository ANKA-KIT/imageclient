#include "mainwindow.h"
#include "ui_mainwindow.h"

//Constructor of TangoProperties
TangoProperties::TangoProperties(MainWindow *main){
    TangoProperties *MainWind = this;
    parent = main;
    centralWidget = new QWidget(MainWind);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(660, 50);
    this->move(100,100);

    /*init buttons*/
    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(560, 20, 91, 24));

    btNewDev = new QPushButton(centralWidget);
    btNewDev->setObjectName(QString::fromUtf8("btNewDev"));
    btNewDev->setGeometry(QRect(460, 20, 91, 24));

    btChangeDevice = new QPushButton(centralWidget);
    btChangeDevice->setObjectName(QString::fromUtf8("btChangeDevice"));
    btChangeDevice->setGeometry(QRect(360, 20, 91, 24));

    /*init labels and text lines*/
    tlServer = new QLineEdit(centralWidget);
    tlServer->setObjectName(QString::fromUtf8("tlServer"));
    tlServer->setGeometry(QRect(80, 0, 171, 20));
    lbServer = new QLabel(centralWidget);
    lbServer->setObjectName(QString::fromUtf8("lbServer"));
    lbServer->setGeometry(QRect(5, 0, 71, 16));

    tlDevice = new QLineEdit(centralWidget);
    tlDevice->setObjectName(QString::fromUtf8("tlDevice"));
    tlDevice->setGeometry(QRect(340, 0, 113, 20));
    lbDevice = new QLabel(centralWidget);
    lbDevice->setObjectName(QString::fromUtf8("lbDevice"));
    lbDevice->setGeometry(QRect(260, 0, 72, 16));

    lbAttr = new QLabel(centralWidget);
    lbAttr->setObjectName(QString::fromUtf8("lbAttr"));
    lbAttr->setGeometry(QRect(460, 0, 71, 16));
    tlAttr = new QLineEdit(centralWidget);
    tlAttr->setObjectName(QString::fromUtf8("tlAttr"));
    tlAttr->setGeometry(QRect(520, 0, 113, 20));

    /*init start text*/
    tlServer->setText("anka-tango3.ka.fzk.de:10000");
    lbServer->setText("Server name");
    lbAttr->setText("Attribute");
    tlAttr->setText("testImage");
    lbDevice->setText("Device name");
    tlDevice->setText("sys/tg_test/mytest");
    btNewDev->setText("Start new Dev");
    btChangeDevice->setText("Set Dev");
    btCancel->setText("Cancel");
    fprintf(stderr, "in TangoProperties constructor\n");
}

//Destructor of TangoProperties
TangoProperties::~TangoProperties(){
    fprintf(stderr, "in TangoProperties destructor\n");
    delete tlAttr;
    delete tlDevice;
    delete tlServer;
    delete lbServer;
    delete lbDevice;
    delete lbAttr;
    delete centralWidget;
}

void TangoProperties::cancel(){
    this->close();
    delete this;
}
