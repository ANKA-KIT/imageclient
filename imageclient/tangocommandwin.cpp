#include "tangocommandwin.h"

TangoCommandWin::TangoCommandWin(QString ser)// : QWidget(parent)
{
    _serverName = ser;
    this->setFixedSize(260, 100);
    this->move(100,100);
    setWindowTitle("Send Tango Command");

    btCancel = new QPushButton(this);
    btCancel->setStatusTip(tr("Cancel, Close this window"));
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(35, 220, 91, 20));
    btOk = new QPushButton(this);
    btOk->setObjectName(QString::fromUtf8("btOk"));
    btOk->setStatusTip(tr("Set This Tango Variables"));
    btOk->setGeometry(QRect(130, 220, 101, 20));

    tlProp = new PropertyLineEdit(this, false);
    tlProp->setStatusTip(tr("Set a Tango command"));
    tlProp->setObjectName(QString::fromUtf8("tlProp"));
   // tlProp->setGeometry(QRect(80, 75, 171, 20));
    QObject::connect(tlProp, SIGNAL(setVal(int)), this, SLOT(onOk()));
    btOk->setText("Set");
    btCancel->setText("Cancel");
    tlProp->setText("getnewpic");

    QObject::connect(btOk, SIGNAL(clicked()),SLOT(onOk()));
    QObject::connect(btCancel, SIGNAL(clicked()), this, SLOT(onCancel()));



    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("Server Command"),tlProp);
    formLayout->addRow(btOk,btCancel);
    setLayout(formLayout);
}

void TangoCommandWin::onOk(){
    ImageTangoDevice *dev = new ImageTangoDevice();
    dev->checkDevice(_serverName);
    dev->setSource(_serverName,"");
    if (dev->sendCommand(tlProp->text())){
        deleteLater();
    }
    delete dev;
}

void TangoCommandWin::onCancel(){
    deleteLater();
}
