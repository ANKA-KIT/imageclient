#include "starttangowin.h"

void StartTangoWindow::refresh(const TVariant &newVal)
{
    if (newVal.quality() == Tango::ATTR_INVALID)
    {
        status->setText("Error");
        return;}
    else{
        emit dev(tlServer->text() +(QString)"/" + tlDevice->text(), tlAttr->text());//source());
        writeSettings();
        deleteLater();
    }
}

StartTangoWindow::StartTangoWindow(QWidget *parent) : QWidget(parent),
   TDevice(this)// QTangoComProxyReader(this)//, QTangoWidgetCommon(this)
{
    connect(device(), SIGNAL(newTangoData(const TVariant&)), this, SLOT(refresh(const TVariant&)),
            Qt::DirectConnection);
    connect(device(), SIGNAL(tangoError(QString)), this, SLOT(testOnError(QString)),
            Qt::DirectConnection);

    qDebug("in StartTangoWin constructor");
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(350, 165);
    this->move(100,100);
    this->setWindowTitle("Set TANGO Device");

    initButtons();
    initTextLine();
    initText();
    initTangoDev();

    QFormLayout *layout = new QFormLayout;
    layout->addRow(lbServer,cmbHost);
    layout->addRow(lbDevice, cmbDevice);
    layout->addRow(lbAttr, cmbAttr);
    layout->addRow(status);
    layout->addRow(btChangeDevice, btCancel);

    centralWidget->setLayout(layout);
    cmbHost->setLineEdit(tlServer);
    cmbDevice->setLineEdit(tlDevice);
    cmbAttr->setLineEdit(tlAttr);

    QObject::connect(this->btChangeDevice, SIGNAL(clicked()),SLOT(onOk()));
    QObject::connect(btCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

    readSettings();
}

int StartTangoWindow::findLastEnteredIndex(QStringList cmb, QString str){
    int i=0;
    for (i; i<cmb.count(); i++){
        if (cmb.at(i) == str){
            break;
        }
    }
    return i;
}

void StartTangoWindow::readSettings(){
    QSettings settings("Vasil","imageClient");
 /*   QString host = settings.value("tangoHost", QString("anka-tango3.ka.fzk.de:10000")).toString();
    QString dev = settings.value("tangoDev", QString("sys/tg_test/mytest")).toString();
    QString attrImage = settings.value("tangoImgAttr", QString("testimage")).toString();
    lsDev = settings.value("tangoDevList", QStringList("sys/tg_test/mytest")).toStringList();
    lsAttr = settings.value("tangoAttrList", QStringList("testimage")).toStringList();
    lsHost = settings.value("tangoHostList", QStringList("anka-tango3.ka.fzk.de:10000")).toStringList();
*/
    QString host = settings.value("tangoHost", QString("localhost:10000")).toString();
    QString dev = settings.value("tangoDev", QString("web/web_test/camera")).toString();
    QString attrImage = settings.value("tangoImgAttr", QString("image")).toString();
    lsDev = settings.value("tangoDevList", QStringList("web/web_test/camera")).toStringList();
    lsAttr = settings.value("tangoAttrList", QStringList("image")).toStringList();
    lsHost = settings.value("tangoHostList", QStringList("localhost:10000")).toStringList();

    cmbDevice->addItems(lsDev);
    cmbAttr->addItems(lsAttr);
    cmbHost->addItems(lsHost);

    cmbDevice->setCurrentIndex(findLastEnteredIndex(lsDev, dev));
    cmbHost->setCurrentIndex(findLastEnteredIndex(lsHost, host));
    cmbAttr->setCurrentIndex(findLastEnteredIndex(lsAttr, attrImage));
}

bool StartTangoWindow::curValIsSet(QStringList listVal, QString str){
    bool isItSet= false;
    for (int i =0; i<listVal.count(); i++){
        if (listVal.at(i) == str){
            isItSet = true;
            break;
        }
    }
    return isItSet;
}

void StartTangoWindow::writeSettings(){
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

void StartTangoWindow::onCancel(){
    //emit cancel();
    deleteLater();
}

void StartTangoWindow::onOk(){
    QString s = tlServer->text() +(QString)"/" + tlDevice->text();//(QString)"//" + tlServer->text() +(QString)"\/" +
    setSource(s, tlAttr->text());
}

void StartTangoWindow::initButtons(){
    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(165, 100, 91, 24));

    btChangeDevice = new QPushButton(centralWidget);
    btChangeDevice->setObjectName(QString::fromUtf8("btChangeDevice"));
    btChangeDevice->setGeometry(QRect(70, 100, 91, 24));
}

void StartTangoWindow::initText(){
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

void StartTangoWindow::initTextLine(){
    tlServer = new PropertyLineEdit(centralWidget, false);
    QObject::connect(tlServer, SIGNAL(setVal(int)), this, SLOT(onOk()));
    lbServer = new QLabel(centralWidget);
    lbServer->setObjectName(QString::fromUtf8("lbServer"));
    lbServer->setGeometry(QRect(5, 0, 71, 16));

    tlDevice = new PropertyLineEdit(centralWidget, false);
    QObject::connect(tlDevice, SIGNAL(setVal(int)), this, SLOT(onOk()));
    lbDevice = new QLabel(centralWidget);
    lbDevice->setObjectName(QString::fromUtf8("lbDevice"));
    lbDevice->setGeometry(QRect(5, 25, 72, 16));

    lbAttr = new QLabel(centralWidget);
    lbAttr->setObjectName(QString::fromUtf8("lbAttr"));
    lbAttr->setGeometry(QRect(5, 50, 71, 16));
    tlAttr = new PropertyLineEdit(centralWidget, false);
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

void StartTangoWindow::initTangoDev(){
    status = new QLabel(centralWidget);
    status->setObjectName(QString::fromUtf8("status"));
    status->setGeometry(QRect(5, 75, 113, 20));
}

void StartTangoWindow::testOnError(QString str){
   qDebug("Was Tango Error You are in testOnError");
   status->setText(str);
}

void StartTangoWindow::testOnOk(){
   qDebug("OK StartTangoWin::testOnOk");
   status->setText("Ok");
}
void StartTangoWindow::testOnOkImgVal(){
    qDebug("\nCORRect img val\n");
    qDebug("Attention, in StartTangoWin pingTimer STOPED");
    emit dev(tlServer->text() +(QString)"\/" + tlDevice->text(), tlAttr->text());//(source());
    writeSettings();
    deleteLater();
}
