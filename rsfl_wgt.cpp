#include "rsfl_wgt.h"

RSFL_WGT::RSFL_WGT(QList <MyDevProperty *> &prop, QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(200, 100);
    if (prop.at(SCALE)!= NULL)
        scale = new Scl_WGT(prop.at(SCALE)->getValue().toDouble(), this);
    else
        scale = new Scl_WGT();// NULL;
    scale->move(0, 60);
    setFliping(prop.at(HOR_FLIP)->getValue().toBool(),prop.at(VER_FLIP)->getValue().toBool());
    setRotation(prop.at(ROTATION)->getValue().toInt());

    connect(hFl, SIGNAL(toggled(bool)), this, SLOT(horFlipSlot(bool)));
    connect(vFl, SIGNAL(toggled(bool)), this, SLOT(verFlipSlot(bool)));
    connect(rotation,SIGNAL(currentIndexChanged(QString)),this,SLOT(rotationSlot(QString)));
}

RSFL_WGT::~RSFL_WGT(){
    delete vFl;
    delete hFl;
    delete scale;
    delete rotation;
    delete lbRotation;
}

void RSFL_WGT::setFliping(bool hor, bool ver){
    vFl = new QCheckBox(this);
    vFl->resize(200,20);
    vFl->move(0, 20);
    vFl->setText("Fertical Flip");
    hFl = new QCheckBox(this);
    hFl->resize(200,20);
    hFl->move(0, 40);
    hFl->setText("Horizontal Flip");

    hFl->setChecked(hor);
    vFl->setChecked(ver);
}

void RSFL_WGT::setRotationVal(int stVal){
    int curRotIndex;
    switch(stVal){
        case -270: curRotIndex=0; break;
        case -180: curRotIndex=1; break;
        case -90: curRotIndex=2; break;
        case 0: curRotIndex=3; break;
        case 90: curRotIndex=4; break;
        case 180: curRotIndex=5; break;
        case 270: curRotIndex=6; break;
    }
    rotation->setCurrentIndex(curRotIndex);
}

void RSFL_WGT::setRotation(int stVal){
    lbRotation= new QLabel("Rotation", this);
    lbRotation->move (0,0);
    lbRotation->resize (60,16);
    rotation = new QComboBox(this);
    rotation->move(70, 0);
    rotation->addItems(QStringList()<<"-270"<<"-180"<<"-90"<<"0"<<"90"<<"180"<<"270");
    setRotationVal(stVal);
}

void RSFL_WGT::horFlipSlot(bool val){
    emit sendHorFlipVal(val);
}
void RSFL_WGT::verFlipSlot(bool val){
    emit sendVerFlipVal(val);
}
void RSFL_WGT::rotationSlot(QString val){
    emit sendRotationVal(val);
}

