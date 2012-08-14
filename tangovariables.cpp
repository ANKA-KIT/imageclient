#include "tangovariables.h"

TangoVariables::TangoVariables(QWidget *parent) //:QWidget(parent)
{
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(260, 250);
    this->move(100,100);
    setWindowTitle("TangoVariables");

    btCancel = new QPushButton(centralWidget);
    btCancel->setStatusTip(tr("Cancel, Close this window"));
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(35, 220, 91, 20));
    btOk = new QPushButton(centralWidget);
    btOk->setObjectName(QString::fromUtf8("btOk"));
    btOk->setStatusTip(tr("Set This Tango Variables"));
    btOk->setGeometry(QRect(130, 220, 101, 20));

    lbImg = new QLabel(centralWidget);
    lbImg->setObjectName(QString::fromUtf8("lbImg"));
    lbImg->setGeometry(QRect(5, 0, 71, 16));
    tlImg = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlImg->setStatusTip(tr("Set Tango Variables for geting Image"));
    tlImg->setObjectName(QString::fromUtf8("tlImg"));
    tlImg->setGeometry(QRect(80, 0, 171, 20));
    QObject::connect(tlImg, SIGNAL(setVal(int)), this, SLOT(onOk()));

    lbRot = new QLabel(centralWidget);
    lbRot->setObjectName(QString::fromUtf8("lbRot"));
    lbRot->setGeometry(QRect(5, 25, 71, 16));
    tlRot = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlRot->setStatusTip(tr("Set Tango Variables for Rotation"));
    tlRot->setObjectName(QString::fromUtf8("tlRot"));
    tlRot->setGeometry(QRect(80, 25, 171, 20));
    QObject::connect(tlRot, SIGNAL(setVal(int)), this, SLOT(onOk()));

    lbBr = new QLabel(centralWidget);
    lbBr->setObjectName(QString::fromUtf8("lbBr"));
    lbBr->setGeometry(QRect(5, 50, 71, 16));
    tlBr = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlBr->setStatusTip(tr("Set Tango Variables for Brightness"));
    tlBr->setObjectName(QString::fromUtf8("tlBr"));
    tlBr->setGeometry(QRect(80, 50, 171, 20));
    QObject::connect(tlBr, SIGNAL(setVal(int)), this, SLOT(onOk()));

    lbCon = new QLabel(centralWidget);
    lbCon->setObjectName(QString::fromUtf8("lbCon"));
    lbCon->setGeometry(QRect(5, 75, 71, 16));
    tlCon = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlCon->setStatusTip(tr("Set Tango Variables for Contrast"));
    tlCon->setObjectName(QString::fromUtf8("tlCon"));
    tlCon->setGeometry(QRect(80, 75, 171, 20));
    QObject::connect(tlCon, SIGNAL(setVal(int)), this, SLOT(onOk()));

    lbGam = new QLabel(centralWidget);
    lbGam->setObjectName(QString::fromUtf8("lbGam"));
    lbGam->setGeometry(QRect(5, 100, 71, 16));
    tlGam = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlCon->setStatusTip(tr("Set Tango Variables for Gamma"));
    tlGam->setObjectName(QString::fromUtf8("tlGam"));
    tlGam->setGeometry(QRect(80, 100, 171, 20));
    QObject::connect(tlGam, SIGNAL(setVal(int)), this, SLOT(onOk()));

    lbScl = new QLabel(centralWidget);
    lbScl->setObjectName(QString::fromUtf8("lbScl"));
    lbScl->setGeometry(QRect(5, 125, 71, 16));
    tlScl = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlScl->setStatusTip(tr("Set Tango Variables for Scale// Not Used in Current Version!!"));
    tlScl->setObjectName(QString::fromUtf8("tlScl"));
    tlScl->setGeometry(QRect(80, 125, 171, 20));
    QObject::connect(tlScl, SIGNAL(setVal(int)), this, SLOT(onOk()));

    lbHorFl = new QLabel(centralWidget);
    lbHorFl->setObjectName(QString::fromUtf8("lbHorFl"));
    lbHorFl->setGeometry(QRect(5, 150, 71, 16));
    tlHorFl = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlHorFl->setStatusTip(tr("Set Tango Variables for Horizontal Fliping"));
    tlHorFl->setObjectName(QString::fromUtf8("tlHorFl"));
    tlHorFl->setGeometry(QRect(80, 150, 171, 16));
    QObject::connect(tlHorFl, SIGNAL(setVal(int)), this, SLOT(onOk()));

    lbVerFl = new QLabel(centralWidget);
    lbVerFl->setObjectName(QString::fromUtf8("lbVerFl"));
    lbVerFl->setGeometry(QRect(5, 175, 71, 16));
    tlVerFl = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlVerFl->setStatusTip(tr("Set Tango Variables for Vertiacal Fliping"));
    tlVerFl->setObjectName(QString::fromUtf8("tlVerFl"));
    tlVerFl->setGeometry(QRect(80, 175, 171, 20));
    QObject::connect(tlVerFl, SIGNAL(setVal(int)), this, SLOT(onOk()));

    lbImgData = new QLabel(centralWidget);
    lbImgData->setObjectName(QString::fromUtf8("lbImgData"));
    lbImgData->setGeometry(QRect(5, 200, 71, 16));
    tlImgData = new MyLineEdit((QLineEdit*)centralWidget, false);
    tlImgData->setStatusTip(tr("Set Tango Variables for getting information about 16 bit IMGAG// Not Used in current version!!!"));
    tlImgData->setObjectName(QString::fromUtf8("tlImgData"));
    tlImgData->setGeometry(QRect(80, 200, 171, 20));
    QObject::connect(tlImgData, SIGNAL(setVal(int)), this, SLOT(onOk()));

    btOk->setText("Set");
    btCancel->setText("Cancel");

    lbRot->setText("Rotation");
    lbBr->setText("Brightness");
    lbCon->setText("Contrast");
    lbGam->setText("Gamma");
    lbScl->setText("Scale");
    lbHorFl->setText("Hor Flip");
    lbVerFl->setText("Ver Flip");
    lbImg->setText("Image");
    tlImg->setText("TestImage");//"TestImage");
    lbImgData->setText("16BitData");
    tlImgData->setText("UShortImg");//"TestImage");

    QObject::connect(btOk, SIGNAL(clicked()),SLOT(onOk()));
    QObject::connect(btCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

    readSettings();
}

TangoVariables::~TangoVariables(){
    delete lbImg;
    delete lbRot;
    delete lbBr;
    delete lbCon;
    delete lbGam;
    delete lbScl;
    delete lbHorFl;
    delete lbVerFl;
    delete tlImg;
    delete tlRot;
    delete tlBr;
    delete tlCon;
    delete tlGam;
    delete tlScl;
    delete tlHorFl;
    delete tlVerFl;
    delete lbImgData;
    delete tlImgData;
    delete centralWidget;
}

void TangoVariables::readSettings(){
    QSettings settings("Vasil","imageClient");
    QString attrImage = settings.value("tangoImgAttr", QString("testImage")).toString();
    QString attrRot = settings.value("tangoRotAttr", QString("Rotate")).toString();
    QString attrBr = settings.value("tangoBrAttr", QString("")).toString();
    QString attrGm = settings.value("tangoGmAttr", QString("")).toString();
    QString attrCon = settings.value("tangoConAttr", QString("")).toString();
    QString attrHFl = settings.value("tangoHFlipAttr", QString("FlipHorizontal")).toString();
    QString attrVFl = settings.value("tangoVFlipAttr", QString("FlipVertical")).toString();
    QString attr16B = settings.value("tango16BitAttr", QString("")).toString();

    tlImg->setText(attrImage);
    tlImgData->setText(attr16B);
    tlBr->setText(attrBr);
    tlCon->setText(attrCon);
    tlGam->setText(attrGm);
    tlRot->setText(attrRot);
    tlHorFl->setText(attrHFl);
    tlVerFl->setText(attrVFl);
}

void TangoVariables::writeSettings(){
    QSettings settings("Vasil","imageClient");
    settings.setValue("tangoImgAttr", tlImg->text());
    settings.setValue("tangoRotAttr", tlRot->text());
    settings.setValue("tangoBrAttr", tlBr->text());
    settings.setValue("tangoGmAttr", tlGam->text());
    settings.setValue("tangoConAttr", tlCon->text());
    settings.setValue("tangoHFlipAttr", tlHorFl->text());
    settings.setValue("tangoVFlipAttr", tlVerFl->text());
    settings.setValue("tango16BitAttr", tlImgData->text());
}


void TangoVariables::onOk(){
    QStringList ls;
    //enum VideoSettingsWinValue{BRIGHTNESS = 0, CONTRAST = 1, GAMMA = 2, ROTATION = 3, SCALE = 4, HOR_FLIP = 5, VER_FLIP = 6,

    ls<<tlBr->text();
    ls<<tlCon->text();
    ls<<tlGam->text();
    ls<<tlRot->text();
    ls<<tlScl->text();
    ls<<tlHorFl->text();
    ls<<tlVerFl->text();
    ls<<tlImg->text();
    ls<<tlImgData->text();


    writeSettings();
    emit setVar(ls);
    emit cancel();
}
void TangoVariables::onCancel(){
    emit cancel();
}
