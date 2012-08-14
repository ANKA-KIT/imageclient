#include "starttangowin.h"

StartTangoWin::StartTangoWin(MainWindow *parent)
//StartTangoWin::StartTangoWin(QWidget *parent) : QWidget(parent)
{
    qDebug("in StartTangoWin constructor");
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(260, 130);
    this->move(100,100);
    this->setWindowTitle("Set TANGO properties");

    initButtons();
    initTextLine();
    initText();

    cmbHost->setLineEdit(tlServer);
    cmbDevice->setLineEdit(tlDevice);
    cmbAttr->setLineEdit(tlAttr);
    initTangoDev();
    QObject::connect(this->btChangeDevice, SIGNAL(clicked()),SLOT(onOk()));
    QObject::connect(btCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

    readSettings();
}


StartTangoWin::~StartTangoWin(){
    qDebug("in StartTangoWin destructor");
    delete lbServer;
    delete lbDevice;
    delete lbAttr;
    delete centralWidget;

    delete cmbDevice;
    delete cmbAttr;
    delete cmbHost;
    delete myDev;
    myDev = NULL;
}

int StartTangoWin::findLastEnteredIndex(QStringList cmb, QString str){
    int i=0;
    for (i; i<cmb.count(); i++){
        if (cmb.at(i) == str){
            break;
        }
    }
    return i;
}

void StartTangoWin::readSettings(){
    QSettings settings("Vasil","imageClient");
    QString host = settings.value("tangoHost", QString("anka-tango3.ka.fzk.de:10000")).toString();
    QString dev = settings.value("tangoDev", QString("sys/tg_test/mytest")).toString();
    QString attrImage = settings.value("tangoImgAttr", QString("testimage")).toString();
    lsDev = settings.value("tangoDevList", QStringList("sys/tg_test/mytest")).toStringList();
    lsAttr = settings.value("tangoAttrList", QStringList("testimage")).toStringList();
    lsHost = settings.value("tangoHostList", QStringList("anka-tango3.ka.fzk.de:10000")).toStringList();

    cmbDevice->addItems(lsDev);
    cmbAttr->addItems(lsAttr);
    cmbHost->addItems(lsHost);

    cmbDevice->setCurrentIndex(findLastEnteredIndex(lsDev, dev));
    cmbHost->setCurrentIndex(findLastEnteredIndex(lsHost, host));
    cmbAttr->setCurrentIndex(findLastEnteredIndex(lsAttr, attrImage));
}

bool StartTangoWin::curValIsSet(QStringList listVal, QString str){
    bool isItSet= false;
    for (int i =0; i<listVal.count(); i++){
        if (listVal.at(i) == str){
            isItSet = true;
            break;
        }
    }
    return isItSet;
}

void StartTangoWin::writeSettings(){
    QSettings settings("Vasil","imageClient");
    settings.setValue("tangoHost", tlServer->text());
    settings.setValue("tangoDev", tlDevice->text());
    settings.setValue("tangoImgAttr", tlAttr->text());

    if (!curValIsSet(lsDev,cmbDevice->currentText()))
        lsDev<<cmbDevice->currentText();
    if (!curValIsSet(lsAttr,cmbAttr->currentText()))
        lsAttr<<cmbAttr->currentText();
    if (!curValIsSet(lsHost,cmbHost->currentText()))
        lsHost<<cmbHost->currentText();
     settings.setValue("tangoHostList", lsHost);
     settings.setValue("tangoAttrList", lsAttr);
     settings.setValue("tangoDevList", lsDev);
}

void StartTangoWin::onCancel(){
    emit cancel();
}

void StartTangoWin::onOk(){
    QString serv = tlServer->text();
    QString dev = tlDevice->text();
    myDev->initDevice(serv, dev);

    myDev->attrImg = tlAttr->text();
    myDev->_serverName = (QString)"\/\/" + tlServer->text() +
                          (QString)"\/" + tlDevice->text();
}

void StartTangoWin::initButtons(){
    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(165, 100, 91, 24));

    btChangeDevice = new QPushButton(centralWidget);
    btChangeDevice->setObjectName(QString::fromUtf8("btChangeDevice"));
    btChangeDevice->setGeometry(QRect(70, 100, 91, 24));
}

void StartTangoWin::initText(){
 //   tlServer->setText("anka-tango3.ka.fzk.de:10000");
    lbServer->setText("Server name");
    lbAttr->setText("Attribute");
 //   tlAttr->setText("testImage");
    //tlAttr->setText("gray16");
    lbDevice->setText("Device name");
 //   tlDevice->setText("sys/tg_test/mytest");
    //tlDevice->setText("iss/ucadevice/image");
    btChangeDevice->setText("Set Dev");
    btCancel->setText("Cancel");
}

void StartTangoWin::initTextLine(){
    tlServer = new MyLineEdit((QLineEdit*)centralWidget, false);
    QObject::connect(tlServer, SIGNAL(setVal(int)), this, SLOT(onOk()));
    lbServer = new QLabel(centralWidget);
    lbServer->setObjectName(QString::fromUtf8("lbServer"));
    lbServer->setGeometry(QRect(5, 0, 71, 16));

    tlDevice = new MyLineEdit((QLineEdit*)centralWidget, false);
    QObject::connect(tlDevice, SIGNAL(setVal(int)), this, SLOT(onOk()));
    lbDevice = new QLabel(centralWidget);
    lbDevice->setObjectName(QString::fromUtf8("lbDevice"));
    lbDevice->setGeometry(QRect(5, 25, 72, 16));

    lbAttr = new QLabel(centralWidget);
    lbAttr->setObjectName(QString::fromUtf8("lbAttr"));
    lbAttr->setGeometry(QRect(5, 50, 71, 16));
    tlAttr = new MyLineEdit((QLineEdit*)centralWidget, false);
    QObject::connect(tlAttr, SIGNAL(setVal(int)), this, SLOT(onOk()));

    cmbDevice = new QComboBox(this);
    cmbDevice->move(80, 25);
    cmbDevice->resize(172, 20);
    cmbDevice->setEditable(true);

    cmbAttr = new QComboBox(this);
    cmbAttr->move(80, 50);
    cmbAttr->resize(170, 20);
    cmbAttr->setEditable(true);

    cmbHost = new QComboBox(this);
    cmbHost->move(80, 0);
    cmbHost->resize(171, 20);
    cmbHost->setEditable(true);
}

void StartTangoWin::initTangoDev(){
    status = new QLabel(centralWidget);
    status->setObjectName(QString::fromUtf8("status"));
    status->setGeometry(QRect(5, 75, 113, 20));
    myDev = new my_Device();
    QObject::connect(myDev, SIGNAL(sendError(QString)), this, SLOT(testOnError(QString)));
    QObject::connect(myDev, SIGNAL(goodConnection()), this, SLOT(testOnOk()));
    QObject::connect(myDev, SIGNAL(correctImgAttrVal()), this, SLOT(testOnOkImgVal()));
}

void StartTangoWin::testOnError(QString str){
   qDebug("Was Tango Error You are in testOnError");
   status->setText(str);
}

void StartTangoWin::testOnOk(){
   qDebug("OK StartTangoWin::testOnOk");
   status->setText("Ok");
   myDev->setTangoAttr(*myDev->device, myDev->attrImg);
}
void StartTangoWin::testOnOkImgVal(){
    qDebug("\nCORRect img val\n");

    qDebug("ServName=   " + myDev->_serverName.toAscii());
    myDev->pingTimer.stop();
    qDebug("Attention, in StartTangoWin pingTimer STOPED");
    writeSettings();
    emit correctDev(myDev->_serverName, myDev->attrImg);
}
