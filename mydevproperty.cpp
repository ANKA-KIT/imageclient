#include "mydevproperty.h"

void MyDevProperty::setValue(QVariant val){
    _val = val;
    emit setVal(val);
    emit repaint(0);
}

QVariant MyDevProperty::getValue(){
    return _val;
}

QString MyDevProperty::getPropName(){
    return _propName;
}

void MyDevProperty::setAttrName(QString val){
    _attr = val;
}

QString MyDevProperty::getAttrName(){
    return _attr;
}

Brightness::Brightness(){
    _propName = "Brightness";
    _val = 0;
}

Contrast::Contrast(){
    _propName = "Contrast";
    _val = 100;
}

Gamma::Gamma(){
    _propName = "Gamma";
    _val = 100;
}

Scale::Scale(){
    _propName = "Scale";
    _val = 1;
}

void Scale::setValue(QVariant val){
    if (val.toDouble() !=0){
        _val = val;
        emit setVal(val);
        emit repaint(0);
    }
    else{
        qDebug("~!!!!!!!!!SCALE 00000!!!!!!");
    }
}

Rotation::Rotation(){
    _propName = "Rotation";
    _val = 0;
}

HorFlip::HorFlip(){
    _propName = "Hor_Flip";
    _val = false;
}

VerFlip::VerFlip(){
    _propName = "Ver_Flip";
    _val = false;
}
