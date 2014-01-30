#include "tangoservervariableswin.h"

TangoServerVariablesWin::TangoServerVariablesWin(QString ser){
    _serverName = ser;
    this->setFixedSize(260, 100);
    this->move(100,100);
    setWindowTitle("TangoVariables");

    btCancel = new QPushButton(this);
    btCancel->setStatusTip(tr("Cancel, Close this window"));
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(35, 220, 91, 20));
    btOk = new QPushButton(this);
    btOk->setObjectName(QString::fromUtf8("btOk"));
    btOk->setStatusTip(tr("Set This Tango Variables"));
    btOk->setGeometry(QRect(130, 220, 101, 20));

    tlProp = new PropertyLineEdit(this, false);
    tlProp->setStatusTip(tr("Set Tango Variable for Tango property"));
    tlProp->setObjectName(QString::fromUtf8("tlProp"));
   // tlProp->setGeometry(QRect(80, 75, 171, 20));
    QObject::connect(tlProp, SIGNAL(setVal(int)), this, SLOT(onOk()));
    btOk->setText("Set");
    btCancel->setText("Cancel");
    tlProp->setText("ServerParameter");

    QObject::connect(btOk, SIGNAL(clicked()),SLOT(onOk()));
    QObject::connect(btCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("Server Property"),tlProp);
    formLayout->addRow(btOk,btCancel);
    setLayout(formLayout);
}

void TangoServerVariablesWin::writeSettings(){
    QSettings settings("Vasil","imageClient");
    //settings.setValue("tangoImgAttr", tlImg->text());
    settings.setValue("tangoPropertyAttr", tlProp->text());
}

void TangoServerVariablesWin::readSettings(){
    QSettings settings("Vasil","imageClient");
    QString attrImage = settings.value("tangoPropertyAttr", QString("testImage")).toString();

    tlProp->setText(attrImage);
}

void TangoServerVariablesWin::onOk(){
    ImageTangoDevice *dev = new ImageTangoDevice();
    if (dev->checkAttr(_serverName, tlProp->text())){
        writeSettings();
        emit setVar(tlProp->text());
        deleteLater();
    }
}

void TangoServerVariablesWin::onCancel(){
    deleteLater();
}
