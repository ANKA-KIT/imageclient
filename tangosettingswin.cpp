#include "tangosettingswin.h"

TangoSettingsWin::TangoSettingsWin(int param, QString title, QString prop, QVariant curVal){
    qDebug("in StartTangoWin constructor");
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(660, 50);
    this->move(100,100);
    this->setWindowTitle("Set TANGO properties");


    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(560, 20, 91, 24));
    btOk = new QPushButton(centralWidget);
    btOk->setObjectName(QString::fromUtf8("btOk"));
    btOk->setGeometry(QRect(560, 20, 91, 24));

    tl = new QLineEdit(centralWidget);
    tl->setObjectName(QString::fromUtf8("tl"));
    tl->setGeometry(QRect(80, 0, 171, 20));
    lb = new QLabel(centralWidget);
    lb->setObjectName(QString::fromUtf8("lb"));
    lb->setGeometry(QRect(5, 0, 71, 16));

    btOk->setText("Set");
    btCancel->setText("Cancel");
    setWindowTitle(title);
    tl->setText(curVal.toString());
    lb->setText(prop);
    _dif = false;
    _originVal = 0;
    switch(param){
        case SCALE_CH_ON:
        case ROTATION_CH_ON:
            _originVal = curVal;
            _dif = true;
        case SCALE:
        case ROTATION:
            QObject::connect(this->btOk, SIGNAL(clicked()),SLOT(onOkDouble()));
        break;
        case BRIGHTNESS_CH_ON:
        case CONTRAST_CH_ON:
        case GAMMA_CH_ON:
            _originVal = curVal;
            _dif = true;
        case BRIGHTNESS:
        case GAMMA:
        case CONTRAST:
            QObject::connect(this->btOk, SIGNAL(clicked()),SLOT(onOkInt()));
        break;
        case VER_FLIP:
        case HOR_FLIP:
            QObject::connect(this->btOk, SIGNAL(clicked()),SLOT(onOkBool()));
        break;
        case REALTIMETIMEOUT:
            QObject::connect(this->btOk, SIGNAL(clicked()),SLOT(onOkInt()));
            tl->setText("100");
            lb->setText("TimeOut(ms)");
        break;
        case TANGO_COM:
            QObject::connect(this->btOk, SIGNAL(clicked()),SLOT(onOk()));
            tl->setText("SetDataImage");
            lb->setText("Command");
        break;
    }
    QObject::connect(this->btCancel, SIGNAL(clicked()),SLOT(onCancel()));
}

TangoSettingsWin::~TangoSettingsWin(){
    delete lb;
    delete btOk;
    delete tl;
    delete btCancel;
    delete centralWidget;
}

void TangoSettingsWin::onOk(){
    emit settingChangedS(tl->text());
    emit cancel();
}

void TangoSettingsWin::onOkInt(){
    int value;
    if (converToInt(value)){
        if(_dif) {value += _originVal.toInt();}
        emit settingChanged(value);
        emit settingChangedI(value);
        emit cancel();
    }
    else{
        qDebug("Convert ERROR in Setting int Val");
    }
}
void TangoSettingsWin::onOkDouble(){
    double value;
    if (converToDouble(value)){
        if(_dif) {value += _originVal.toDouble();}
        emit settingChanged(value);
        emit settingChangedD(value);
        emit cancel();
    }
    else{
        qDebug("Convert ERROR in Setting double Val");
    }
}
void TangoSettingsWin::onOkBool(){
    if (tl->text() == "true" || tl->text() == "false"){
        emit settingChanged(tl->text());
        emit settingChangedS(tl->text());
        emit cancel();
    }
    else{
        qDebug("Error, Set correct BOOL Val");
    }
}

void TangoSettingsWin::onCancel(){
    emit cancel();
}

bool TangoSettingsWin::converToInt(int& val){
    bool ok = true;
    int temp;
    temp = tl->text().toInt(&ok);
    if (ok)
        val = temp;
    else
        val = 0;
    return ok;
}

bool TangoSettingsWin::converToDouble(double& val){
    bool ok = true;
    double temp;
    temp = tl->text().toDouble(&ok);
    if (ok)
        val = temp;
    else
        val = 0;
    return ok;
}

//----------------------------------------------------------------------//
SetMarker::SetMarker(){
    setWindowTitle("Set Marker position");
    setFixedSize(100,70);
    move(100,50);
    lbX = new QLabel("X", this);
    lbX->setGeometry(0,0,20,24);
    lbY = new QLabel("Y", this);
    lbY->setGeometry(0,25,20,24);

    tlX = new MyLineEdit((QLineEdit*)this);
    tlX->setGeometry(15, 0, 60, 24);
    tlY = new MyLineEdit((QLineEdit*)this);
    tlY->setGeometry(15,25, 60, 24);

    btOk = new QPushButton("Ok", this);
    btOk->setGeometry(20, 50, 40, 24);
    connect(btOk, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(tlX, SIGNAL(setVal(int)), this, SLOT(onOk()));
    connect(tlY, SIGNAL(setVal(int)), this, SLOT(onOk()));

}
SetMarker::~SetMarker(){
    delete lbX;
    delete lbY;

    delete tlX;
    delete tlY;

    delete btOk;
}

void SetMarker::onOk(){
    bool okX = true;
    bool okY = true;
    int x = tlX->text().toInt(&okX);
    int y = tlY->text().toInt(&okY);

    if(okX && okY){
        emit setMarker(x,y);
        close();
    }
}
