#include "propertymanipulation.h"

Int_WGT::Int_WGT(int curVal,QWidget *parent): QWidget(parent){
    resize(200, 20);
    lb = new QLabel(this);
    lb->move(0,0);
    lb->resize(20, 20);

    slider = new QSlider(this);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setValue(curVal);
    slider->move(20,0);
    slider->resize(130,20);
    slider->setOrientation(Qt::Horizontal);

    line = new MyLineEdit((QLineEdit*)this);
    line->move(150, 0);
    line->resize(50, 20);
    line->setText(QString().number(curVal));
}

void Int_WGT::setVal(int val){
    emit sendVal(val);
}

void Int_WGT::receiveVal(QVariant val){
    slider->setValue(val.toInt());
    line->setText(val.toString());
}

/*
Con_WGT::Con_WGT(int curVal,QWidget *parent){

}
void Con_WGT::setVal(int val){}

Gm_WGT::Gm_WGT(int curVal,QWidget *parent){}
void Gm_WGT::setVal(int val){}

Br_WGT::Br_WGT(int curVal,QWidget *parent){}
void Br_WGT::setVal(int val){}

LBorder_WGT::LBorder_WGT(int curVal,QWidget *parent){}
void LBorder_WGT::LBorder_WGT::setVal(int val){}

RBorder_WGT::RBorder_WGT(int curVal,QWidget *parent){}
void RBorder_WGT::setVal(int val){}
*/
Double_WGT::Double_WGT(double curVal, QWidget *parent) : QWidget(parent){
    resize(200, 20);
    lb = new QLabel(this);
    lb->move(0,0);
    lb->resize(20, 20);

    slider = new QSlider(this);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setValue(curVal);
    slider->move(20,0);
    slider->resize(130,20);
    slider->setOrientation(Qt::Horizontal);

    line = new MyLineEdit((QLineEdit*)this);
    line->move(150, 0);
    line->resize(50, 20);
    line->setText(QString().number(curVal));
}

void Double_WGT::setVal(int val){
    setValD((double)val);
}

void Double_WGT::receiveVal(QVariant val){
    slider->setValue(val.toInt());
    double temp = val.toDouble();
    line->setText(QString().number(temp,'g',4));
}

void Double_WGT::setValD(double val){
    line->setText(QString().number(val, 'g', 4));
    emit sendVal(val);
}

Scl_WGT::Scl_WGT(double curVal, QWidget *parent): Double_WGT(curVal,parent){
    lb->setText("Scl");
    slider->setTickInterval(curVal*1000);
    slider->setSingleStep(100);
   // slider->setValue(curVal);
    slider->setMaximum(5000);
    slider->setMinimum(100);
    line->setText(QString().number(curVal,'g',4));
    QObject::connect(line, SIGNAL(setValD(double)), this, SLOT(setValD(double)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setVal(int)));
}

void Scl_WGT::setVal(int val){
    setValD(val/1000.0);
}

Rot_WGT::Rot_WGT(double curVal,QWidget *parent) : Double_WGT(curVal,parent){
    lb->setText("Rot");
    slider->setTickInterval(8100);
    slider->setSingleStep(270);
    slider->setMaximum(270);
    slider->setMinimum(-270);
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setVal(int)));
    QObject::connect(line, SIGNAL(setValD(double)), this, SLOT(setValD(double)));
}

Binar_WGT::Binar_WGT(QString curVal, QString str,QWidget *parent) : QWidget(parent){
    resize(200, 20);
    lb = new QLabel(this);
    lb->move(0,0);
    lb->resize(20, 20);

    slider = new QSlider(this);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setValue((curVal == "true")?1:0);
    slider->move(20,0);
    slider->resize(130,20);
    slider->setOrientation(Qt::Horizontal);

    value = new QLabel(this);
    value->move(150, 0);
    value->resize(50, 20);
    value->setText(curVal);

    lb->setText(str);
    slider->setTickInterval(1);
    slider->setSingleStep(1);
    slider->resize(130,20);
    slider->setMaximum(1);
    slider->setMinimum(0);
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setVal(int)));
}

void Binar_WGT::setVal(int val){
    bool valBool = (val == 1);
    QString str;
    valBool ? str="true":str="false";
    value->setText(str);
    emit sendVal(valBool);
}

Binar_WGT::~Binar_WGT(){
    delete lb;
    delete slider;
    delete value;
}

Double_WGT::~Double_WGT(){
    delete lb;
    delete slider;
    delete line;
}

Int_WGT::~Int_WGT(){
    delete lb;
    delete slider;
    delete line;
}
