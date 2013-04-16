#include "imagemanipulator.h"

ImageManipulator::ImageManipulator(QList<QVariant> param, QVector<unsigned short> val16, QImage image){
    setWindowTitle("Set Picture Parameters");
    maxBrightness = maxContrast = param[MAXCONTR].toInt();
    initGm(param[GAMMA].toInt());
    initLBorder(param[LBORDER].toInt());
    initRBorder(param[RBORDER].toInt());
    if (param[PICMODE].toInt() == ImagePictureMode::IS_48BIT || param[PICMODE].toInt() == ImagePictureMode::IS_RGB || param[PICMODE].toInt() == ImagePictureMode::IS_RGBA){
        setVisibleBorder(false);
        minContrast = minBrightness  = -param[MAXCONTR].toInt();
        isRGB = true;
    }
    else{
        setVisibleGamma(false);
       minContrast = minBrightness  = 0;

       isRGB = false;
    }
    setRotation(param[ROTATE].toInt());
    initBr(param[BRIGHTNESS].toInt());
    initCon(param[CONTRAST].toInt());
    initScale(param[SCALE].toDouble());
    initFliping(param[VERFLIP].toBool(), param[HORFLIP].toBool());
 /*  if(param[TIMER].toInt() != 0){
        initTimer(param[TIMER].toInt());
    }
*/
    connect(hFl, SIGNAL(toggled(bool)), this, SLOT(horFlipSlot(bool)));
    connect(vFl, SIGNAL(toggled(bool)), this, SLOT(verFlipSlot(bool)));
    connect(rotation,SIGNAL(currentIndexChanged(QString)),this,SLOT(rotationSlot(QString)));

    cmb = new QComboBox(this);
    cmb->setObjectName(QString::fromUtf8("cmb"));
    cmb->setGeometry(QRect(0, 150, 241, 25));
    cmb->addItems(QStringList()<<"QImage::Format_Indexed8"<<"QImage::Format_RGB32"<< "" +
               QString("QImage::Format_ARGB32")<<"QImage::Format_ARGB32_Premultiplied"<< "" +
               QString("QImage::Format_RGB16")<<  "QImage::Format_ARGB8565_Premultiplied" << ""+
               QString("QImage::Format_RGB666") << "QImage::Format_ARGB6666_Premultiplied" <<  ""+
               QString("QImage::Format_RGB555")<<"QImage::Format_ARGB8555_Premultiplied"<< ""+
               QString("QImage::Format_RGB888")<< "QImage::Format_RGB444" << "QImage::Format_ARGB4444_Premultiplied");
    connect(cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFormat(int)));
    cmb->setVisible(false);

    gbHistogram = createHis(param[PICMODE].toInt(), param[LBORDER].toInt(), param[RBORDER].toInt(),val16, image);
    gbHistogram->setGeometry(0,160,450,500);
    connect(gbHistogram, SIGNAL(clicked(bool)), this, SLOT(showHistogramSlot(bool)));

    gbDisplayPicPos = createDisplayPicPos(param[PICX].toString(),param[PICY].toString(),param[DIMX].toString(), param[DIMY].toString());
    gbDisplayPicPos->setGeometry(365, 0,120,100);

    gbDisplayPic = createDisplayPic(param[FULLPICMODE].toBool(),param[PICMODE].toInt(),param[TIMER].toInt());
    gbDisplayPic->setGeometry(0, 110,450,45);
}

QGroupBox* ImageManipulator::createDisplayPic(bool full, int pm, int time){
    QGroupBox* groupbox = new QGroupBox("Display properties", this);
    fullScreen = new QCheckBox("Full Picture", groupbox);
    fullScreen->setGeometry(100, 20, 110, 24);
    fullScreen->setChecked(full);
    connect(fullScreen, SIGNAL(toggled(bool)), this, SLOT(fullScreenSlot(bool)));

    if(time !=0){

        cmbPicMode = new QComboBox(groupbox);
        cmbPicMode->setObjectName(QString::fromUtf8("cmb"));
        cmbPicMode->setGeometry(QRect(250, 20, 200, 25));
        cmbPicMode->addItems(QStringList()<<"IS_16BITGRAY"<<" IS_RGB"<<"IS_48BIT"<<"IS_RGBGRAY"<<"IS_8BIT"<<"IS_RGBA");
        cmbPicMode->setCurrentIndex(pm);
        connect(cmbPicMode, SIGNAL(currentIndexChanged(int)), this, SLOT(changePictureMode(int)));



        lbTimer= new QLabel(groupbox);
        lbTimer->setText("Time");
        lbTimer->move(0,20);
        lbTimer->resize(35, 20);
        TimerLine  = new PropertyLineEdit(groupbox);
        TimerLine->move(35, 20);
        TimerLine->resize(50, 20);
        TimerLine->setText(QString().number(time));
        QObject::connect(TimerLine, SIGNAL(setVal(int)), this, SLOT(setTimer(int)));
    }
    return groupbox;
}

QGroupBox* ImageManipulator::createDisplayPicPos(QString px,QString py, QString dx, QString dy){
    QGroupBox *groupbox = new QGroupBox("Picture position", this);
    picMoveXLine = new PropertyLineEdit(groupbox);
    picMoveXLine->setGeometry(0, 20, 50, 20);
    picMoveXLine->setText(px) ;
    QObject::connect(picMoveXLine, SIGNAL(setVal(int)), this, SLOT(setPicX(int)));

    picMoveYLine = new PropertyLineEdit(groupbox);
    picMoveYLine->setGeometry(55, 20, 50, 20);
    picMoveYLine->setText(py) ;
    QObject::connect(picMoveYLine, SIGNAL(setVal(int)), this, SLOT(setPicY(int)));

    lbPicX  = new QLabel(dx,groupbox);
    lbPicX->setGeometry(0,45, 40,20);
    lbPicY  = new QLabel(dy,groupbox);
    lbPicY->setGeometry(55,45, 40,20);
    lbPicSize = new QLabel("[0 0] ["+QString(px)+" "+QString(py)+"]",groupbox);
    lbPicSize->setGeometry(0,70, 110,20);
    return groupbox;
}

QGroupBox* ImageManipulator::createHis(int p,int l,int r, QVector<unsigned short> val16, QImage image){
    QGroupBox* groupBox = new QGroupBox("histogram", this);
    groupBox->setCheckable(true);
    groupBox->setChecked(false);

    switch(p){
        case ImagePictureMode::IS_16BITGRAY:
            if (val16.size() != 0)
                histogram = new ImageHistogram(val16,p, l,r, groupBox);
            else
                histogram = new ImageHistogram(groupBox);
            break;
        case ImagePictureMode::IS_8BIT:
        case ImagePictureMode::IS_RGBGRAY:
        case ImagePictureMode::IS_48BIT:
        case ImagePictureMode::IS_RGB:
            if (!image.isNull())
                histogram = new ImageHistogram(image,  p, l, r, groupBox);
            else
                histogram = new ImageHistogram(groupBox);
            break;
        default: qDebug("histogram not inited"); histogram = new ImageHistogram(groupBox);
    }
    histogram->move(0,20);

    btNewHis = new QPushButton("Get histogram", groupBox);
    btNewHis->setGeometry(0, 20, 100, 24);
    connect(btNewHis, SIGNAL(clicked()), this, SLOT(onBtNewHisClick()));

    autoNewHis = new QCheckBox("Auto get data", groupBox);
    autoNewHis->setGeometry(300, 20, 120, 24);
    connect(autoNewHis, SIGNAL(toggled(bool)), this, SLOT(autoHistogramSlot(bool)));

    showHistogramSlot(groupBox->isChecked());
    return groupBox;
}

void ImageManipulator::setPicX(int val){
    if (val+20 < lbPicX->text().toInt()){
        emit chPicX(val);
    }
    else{
        lbPicX->setText("");
    }
}

void ImageManipulator::setPicY(int val){
    if (val+20 < lbPicY->text().toInt()){
        emit chPicY(val);
    }
    else{
        lbPicY->setText("");
    }
}

void ImageManipulator::setDim(int valX, int valY){
    if (!fullScreen->isChecked()){
        if (valX != lbPicX->text().toInt()){
            lbPicX->setText(QString().number(valX));
        }
        if (valY != lbPicY->text().toInt()){
            lbPicY->setText(QString().number(valY));
        }
    }
}

void ImageManipulator::setShowPicSize(int x1, int y1, int x2, int y2){
    lbPicSize->setText("[" + QString().number(x1) + "," + QString().number(y1) + "] "+
                       "[" + QString().number(x2) + "," + QString().number(y2) + "]");
}

void ImageManipulator::onBtNewHisClick(){
    emit getDataHistogram();
}

void ImageManipulator::showHistogramSlot(bool val){
    if (val){
        setFixedSize(510, 510);
    }
    else{
        setFixedSize(510, 200);
        autoNewHis->setChecked(false);
    }
}

void ImageManipulator::autoHistogramSlot(bool val){
    emit autoHistogram(val);
}

void ImageManipulator::fullScreenSlot(bool val){
    emit fullScreenMode(val);
    if (val)
        setShowPicSize(0,0,0,0);
}

void ImageManipulator::setRotationVal(int stVal){
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

void ImageManipulator::setRotation(int stVal){
    lbRotation= new QLabel("Rotation", this);
    lbRotation->move (220,5);
    lbRotation->resize (70,16);
    rotation = new QComboBox(this);
    rotation->move(285, 0);
    rotation->addItems(QStringList()<<"-270"<<"-180"<<"-90"<<"0"<<"90"<<"180"<<"270");
    setRotationVal(stVal);
}

void ImageManipulator::initFliping(bool ver, bool hor ){
    vFl = new QCheckBox("Fertical Flip", this);
    vFl->resize(200,20);
    vFl->move(220, 20);
    hFl = new QCheckBox("Horizontal Flip", this);
    hFl->resize(200,20);
    hFl->move(220, 40);

    vFl->setChecked(ver);
    hFl->setChecked(hor);
}



void ImageManipulator::initBr(int stBr){
    lbHisBr = new QLabel(this);
    lbHisBr->setText("Br");
    lbHisBr->move(0,40);
    lbHisBr->resize(20, 20);

    brLine = new PropertyLineEdit(this);
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

void ImageManipulator::initTimer(int time){
    lbTimer= new QLabel(this);
    lbTimer->setText("Time");
    lbTimer->move(0,110);
    lbTimer->resize(25, 20);
    TimerLine  = new PropertyLineEdit(this);
    TimerLine->move(25, 110);
    TimerLine->resize(50, 20);
    TimerLine->setText(QString().number(time));
    QObject::connect(TimerLine, SIGNAL(setVal(int)), this, SLOT(setTimer(int)));
}
void ImageManipulator::initCon(int stContr){
    lbHisCon = new QLabel(this);
    lbHisCon->setText("Con");
    lbHisCon->move(0,60);
    lbHisCon->resize(125, 20);

    conLine  = new PropertyLineEdit(this);
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


void ImageManipulator::initGm(int gm){
    int Y = 20;
    lbHisGm  = new QLabel(this);
    lbHisGm->setText("Gm");
    lbHisGm->move(0,Y);
    lbHisGm->resize(20, 20);

    gamma = new QSlider(this);
    gamma->setFocusPolicy(Qt::StrongFocus);
    gamma->setTickPosition(QSlider::TicksBothSides);
    gamma->setTickInterval(maxContrast-1);
    gamma->setSingleStep(1);
    gamma->move(20,Y);
    gamma->resize(130,20);
    gamma->setValue(gm);
    gamma->setMaximum(1000);
    gamma->setMinimum(-1);
    gamma->setOrientation(Qt::Horizontal);
    QObject::connect(gamma, SIGNAL(valueChanged(int)), this, SLOT(setGmImg(int)));

    gmLine = new PropertyLineEdit(this);
    gmLine->move(150, Y);
    gmLine->resize(50, 20);
    gmLine->setText(QString().number(gm));
    QObject::connect(gmLine, SIGNAL(setVal(int)), this, SLOT(setGmImg(int)));
}


void ImageManipulator::initLBorder(int stLBorder){
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

    leftLine = new PropertyLineEdit(this);
    leftLine->move(150, 0);
    leftLine->resize(50, 20);
    leftLine->setText(QString().number(stLBorder));
    QObject::connect(leftLine, SIGNAL(setVal(int)), this, SLOT(setLeftBorder(int)));
}

void ImageManipulator::initScale(double scl){
    lbScl = new QLabel(this);
    lbScl->setText("Scl");
    lbScl->move(0,80);
    lbScl->resize(20, 20);

    scale = new QSlider(this);
    scale->setFocusPolicy(Qt::StrongFocus);
    scale->setTickPosition(QSlider::TicksBothSides);
    scale->setTickInterval(maxContrast-1);
    scale->setSingleStep(1);
    scale->move(20,80);
    scale->resize(130,20);
    scale->setValue(scl);
    scale->setMaximum(10000);
    scale->setMinimum(1);
    scale->setOrientation(Qt::Horizontal);
    QObject::connect(scale, SIGNAL(valueChanged(int)), this, SLOT(setScale(int)));

    sclLine = new PropertyLineEdit(this);
    sclLine->move(150, 80);
    sclLine->resize(50, 20);
    sclLine->setText(QString().number(scl));
    //QObject::connect(sclLine, SIGNAL(setVal(int)), this, SLOT(setScale(int)));
    QObject::connect(sclLine, SIGNAL(setValD(double)), this, SLOT(setScaleD(double)));
}

void ImageManipulator::initRBorder(int stRBorder){
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

    rightLine = new PropertyLineEdit(this);
    rightLine->move(150, 20);
    rightLine->resize(50, 20);
    rightLine->setText(QString().number(stRBorder));
    QObject::connect(rightLine, SIGNAL(setVal(int)), this, SLOT(setRightBorder(int)));
}

void ImageManipulator::changeFormat(int value){
    emit changeFormatOfColor(value + 3);
}
void ImageManipulator::setRightBorder(int val){
    if (resetParam){
        contr->setValue(maxContrast);
        brig->setValue(0);
    }
    rightLine->setText(QString().number(val));
    emit setRBorder(val);
}


void ImageManipulator::setLeftBorder(int val){
    if (resetParam){
        contr->setValue(maxContrast);
        brig->setValue(0);
    }
    leftLine->setText(QString().number(val));
    emit setLBorder(val);
}

void ImageManipulator::setLeftVal(int val){
    leftBorder->setValue(val);
    setLeftBorder(val);
}

void ImageManipulator::setRightVal(int val){
    if (val > maxContrast){
        val = maxContrast;
    }
    rightBorder->setValue(val);
    setRightBorder(val);
}

void ImageManipulator::setBrImg(int val){
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

void ImageManipulator::setConImg(int val){
    lastContr = val;
    setBrImg(lastbr);
    conLine->setText(QString().number(val));
    emit setCon(lastContr);
}

void ImageManipulator::setGmImg(int val){
    gmLine->setText(QString().number(val));
    emit setGm(val);
}

void ImageManipulator::horFlipSlot(bool val){
    emit sendHorFlipVal(val);
}
void ImageManipulator::verFlipSlot(bool val){
    emit sendVerFlipVal(val);
}
void ImageManipulator::rotationSlot(QString val){
    emit sendRotationVal(val);
}
void ImageManipulator::setVisibleGamma(bool val){
    gmLine->setVisible(val);
    lbHisGm->setVisible(val);
    gamma->setVisible(val);
}
void ImageManipulator::setVisibleBorder(bool val){
    leftBorder->setVisible(val);
    leftLine->setVisible(val);
    lbHisLB->setVisible(val);

    rightBorder->setVisible(val);
    rightLine->setVisible(val);
    lbHisRB->setVisible(val);
}
void ImageManipulator::changePictureMode(int value){
    int minVal, maxVal;
    setVisibleGamma(false);
    setVisibleBorder(true);
    switch(value){
        case ImagePictureMode::IS_16BITGRAY: minVal = 0; maxVal=65535; break;
        case ImagePictureMode::IS_RGBA:
        case ImagePictureMode::IS_RGB: minVal = -3000; maxVal=3000;
            setVisibleGamma(true);
            setVisibleBorder(false);
        break;
        case ImagePictureMode::IS_48BIT: minVal = -3000; maxVal=3000;
            setVisibleGamma(true);
            setVisibleBorder(false);
        break;
        case ImagePictureMode::IS_RGBGRAY: minVal = 0; maxVal=255; break;
        case ImagePictureMode::IS_8BIT:  minVal = 0; maxVal=255; break;
    }
    contr->setMinimum(minVal); contr->setMaximum(maxVal);
    brig->setMinimum(minVal); brig->setMaximum(maxVal);
    leftBorder->setMinimum(minVal); leftBorder->setMaximum(maxVal);
    rightBorder->setMinimum(minVal); rightBorder->setMaximum(maxVal);
    leftLine->setText("0"); rightLine->setText(QString().number(maxVal));
    emit changePictureModeSignal(value);
}
void ImageManipulator::setTimer(int val){
    emit setTime(val);
}
void ImageManipulator::setScaleD(double val){
    emit setScaleSignal(val);
    sclLine->setText(QString().number(val, 'g', 4));
}
void ImageManipulator::setScale(int val){
    setScaleD(val/1000.0);
}
