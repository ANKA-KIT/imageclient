#include "bgcpl_wgt.h"

using namespace br_gm_con_pixLevel;
void BGCPL_WGT::init(){
    resetParam = true;
    lbHisLB  = NULL;
    lbHisRB  = NULL;
    lbHisBr  = NULL;
    lbHisCon  = NULL;

    rightLine  = NULL;
    leftLine = NULL;
    brLine = NULL;
    conLine  = NULL;
    leftBorder  = NULL;
    rightBorder  = NULL;
    brig  = NULL;
    contr  = NULL;

    gmLine = NULL;
    gamma = NULL;
    lbHisGm = NULL;
    resize(200, 100);
}


BGCPL_WGT::BGCPL_WGT(QWidget *parent): QWidget(parent){
    init();
}

void BGCPL_WGT::switchMode(int mode, int gm){
    switch(mode){
        case IS_8BITGREY_MODE:
            init8BitGreyMode();
        break;
        case IS_16BITGREY_MODE:
            init16BitGreyMode();
        break;
        case IS_COLOR_MODE:
            initColorMode(gm);
        break;
    }
}


BGCPL_WGT::BGCPL_WGT(int mode, int br, int con, QWidget *parent, int gm, int lBr, int rBr) : QWidget(parent){
    init();
    stLBorder  = lBr;
    stRBorder = rBr;
    switchMode(mode, gm);
    stContr = con;
    stBr = br;
    initBr();
    initCon();
}

BGCPL_WGT::~BGCPL_WGT(){
    delete lbHisLB;
    delete lbHisRB;
    delete lbHisBr;
    delete lbHisCon;

    delete rightLine;
    delete leftLine;
    delete brLine;
    delete conLine;
    delete leftBorder;
    delete rightBorder;
    delete brig;
    delete contr;

    delete gmLine;
    delete gamma;
    delete lbHisGm;
}

void BGCPL_WGT::init16BitGreyMode(){
    isRGB = false;
    maxContrast = 65535;
    minContrast = 32;
    maxBrightness = 65535;
    minBrightness = 0;


    initLBorder();
    initRBorder();
}


void BGCPL_WGT::init8BitGreyMode(){
    isRGB = false;
    maxContrast = 255;//255;
    minContrast = 1;
    maxBrightness = 255;
    minBrightness = 0;
    stContr = 255;

    initRBorder();
    initLBorder();
}


void BGCPL_WGT::initColorMode(int gm){
    isRGB = true;

    maxContrast = 1500;//255;
    minContrast = -1500;
    maxBrightness = 150;
    minBrightness = -150;
    stContr = 100;

    initGm(gm);
}


void BGCPL_WGT::initBr(){
    lbHisBr = new QLabel(this);
    lbHisBr->setText("Br");
    lbHisBr->move(0,40);
    lbHisBr->resize(20, 20);

    brLine = new MyLineEdit((QLineEdit*)this);
    brLine->move(150, 40);
    brLine->resize(50, 20);
    brLine->setText(QString().number(stBr)) ;
    QObject::connect(brLine, SIGNAL(setVal(int)), this, SLOT(setBrImg(int)));

    brig = new QSlider(this);
    brig->setFocusPolicy(Qt::StrongFocus);
    brig->setTickPosition(QSlider::TicksBothSides);
    brig->setTickInterval(maxBrightness-1);
    brig->setSingleStep(1);
    brig->move(20,40);
    brig->resize(130,20);
    brig->setValue(stBr);
    brig->setMaximum(maxBrightness);
    brig->setMinimum(minBrightness);
    brig->setOrientation(Qt::Horizontal);
    QObject::connect(brig, SIGNAL(valueChanged(int)), this, SLOT(setBrImg(int)));
    lastbr=stBr;
}


void BGCPL_WGT::initCon(){
    lbHisCon = new QLabel(this);
    lbHisCon->setText("Con");
    lbHisCon->move(0,60);
    lbHisCon->resize(25, 20);

    conLine  = new MyLineEdit((QLineEdit*)this);
    conLine->move(150, 60);
    conLine->resize(50, 20);
    conLine->setText(QString().number(stContr));
    QObject::connect(conLine, SIGNAL(setVal(int)), this, SLOT(setConImg(int)));

    contr = new QSlider(this);
    contr->setFocusPolicy(Qt::StrongFocus);
    contr->setTickPosition(QSlider::TicksBothSides);
    contr->setTickInterval(maxContrast-1);
    contr->setSingleStep(1);
    contr->move(20,60);
    contr->resize(130,20);
    contr->setValue(stContr);
    contr->setMaximum(maxContrast);
    contr->setMinimum(minContrast);
    contr->setOrientation(Qt::Horizontal);
    QObject::connect(contr, SIGNAL(valueChanged(int)), this, SLOT(setConImg(int)));
    lastContr = stContr;
}


void BGCPL_WGT::initGm(int gm){
    lbHisGm  = new QLabel(this);
    lbHisGm->setText("Gm");
    lbHisGm->move(0,80);
    lbHisGm->resize(20, 20);

    gamma = new QSlider(this);
    gamma->setFocusPolicy(Qt::StrongFocus);
    gamma->setTickPosition(QSlider::TicksBothSides);
    gamma->setTickInterval(maxContrast-1);
    gamma->setSingleStep(1);
    gamma->move(20,80);
    gamma->resize(130,20);
    gamma->setValue(gm);
    gamma->setMaximum(1000);
    gamma->setMinimum(-1000);
    gamma->setOrientation(Qt::Horizontal);
    QObject::connect(gamma, SIGNAL(valueChanged(int)), this, SLOT(setGmImg(int)));

    gmLine = new MyLineEdit((QLineEdit*)this);
    gmLine->move(150, 80);
    gmLine->resize(50, 20);
    gmLine->setText(QString().number(gm));
    QObject::connect(gmLine, SIGNAL(setVal(int)), this, SLOT(setGmImg(int)));
}


void BGCPL_WGT::initLBorder(){
    lbHisLB = new QLabel(this);
    lbHisLB->setText("L");
    lbHisLB->move(0,0);
    lbHisLB->resize(20, 20);

    leftBorder = new QSlider(this);
    leftBorder->setFocusPolicy(Qt::StrongFocus);
    leftBorder->setTickPosition(QSlider::TicksBothSides);
    leftBorder->setTickInterval(maxContrast-1);
    leftBorder->setSingleStep(1);
    leftBorder->move(20,0);
    leftBorder->resize(130,20);
    leftBorder->setValue(stLBorder);
    leftBorder->setMaximum(maxContrast-1);
    leftBorder->setMinimum(0);
    leftBorder->setOrientation(Qt::Horizontal);
    QObject::connect(leftBorder, SIGNAL(valueChanged(int)), this, SLOT(setLeftBorder(int)));

    leftLine = new MyLineEdit((QLineEdit*)this);
    leftLine->move(150, 0);
    leftLine->resize(50, 20);
    leftLine->setText(QString().number(stLBorder));
    QObject::connect(leftLine, SIGNAL(setVal(int)), this, SLOT(setLeftBorder(int)));
}


void BGCPL_WGT::initRBorder(){
    lbHisRB = new QLabel(this);
    lbHisRB->setText("R");
    lbHisRB->move(0,20);
    lbHisRB->resize(20, 20);

    rightBorder = new QSlider(this);
    rightBorder->setFocusPolicy(Qt::StrongFocus);
    rightBorder->setTickPosition(QSlider::TicksBothSides);
    rightBorder->setTickInterval(maxContrast-1);
    rightBorder->setSingleStep(1);
    rightBorder->move(20,20);
    rightBorder->resize(130,20);
    rightBorder->setValue(stRBorder);
    rightBorder->setMaximum(maxContrast);
    rightBorder->setMinimum(1);
    rightBorder->setOrientation(Qt::Horizontal);
    QObject::connect(rightBorder, SIGNAL(valueChanged(int)), this, SLOT(setRightBorder(int)));

    rightLine = new MyLineEdit((QLineEdit*)this);
    rightLine->move(150, 20);
    rightLine->resize(50, 20);
    rightLine->setText(QString().number(stRBorder));
    QObject::connect(rightLine, SIGNAL(setVal(int)), this, SLOT(setRightBorder(int)));
}


void BGCPL_WGT::setRightBorder(int val){
    if (resetParam){
        contr->setValue(maxContrast);
        brig->setValue(0);
    }
    rightLine->setText(QString().number(val));
    emit setRBorder(val);
}


void BGCPL_WGT::setLeftBorder(int val){
    if (resetParam){
        contr->setValue(maxContrast);
        brig->setValue(0);
    }
    leftLine->setText(QString().number(val));
    emit setLBorder(val);
}

void BGCPL_WGT::setLeftVal(int val){
    leftBorder->setValue(val);
    setLeftBorder(val);
}

void BGCPL_WGT::setRightVal(int val){
    if (val > maxContrast){
        val = maxContrast;
    }
    rightBorder->setValue(val);
    setRightBorder(val);
}

void BGCPL_WGT::setBrImg(int val){
    resetParam = false;
    if (!isRGB){
        int diff = lastContr - val;
        if (diff>0){
            setLeftVal(0);
            setRightVal(lastContr+val/2);
        }
        else{
            setLeftVal(-diff);
            setRightVal(1.5*lastContr-diff);
        }
        lastbr = val;
    }
    brLine->setText(QString().number(val));
    emit setBr(val);
    resetParam = true;
}

void BGCPL_WGT::setConImg(int val){
    lastContr = val;
    setBrImg(lastbr);
    conLine->setText(QString().number(val));
    emit setCon(lastContr);
}

void BGCPL_WGT::setGmImg(int val){
    gmLine->setText(QString().number(val));
    emit setGm(val);
}

void BGCPL_WGT::receiveBr(QVariant val){
    brig->setValue(val.toInt());
    brLine->setText(val.toString());
}
void BGCPL_WGT::receiveCon(QVariant val){
    contr->setValue(val.toInt());
    conLine->setText(val.toString());
}
void BGCPL_WGT::receiveGm(QVariant val){
    gamma->setValue(val.toInt());
    gmLine->setText(val.toString());
}
