#include "slidermanip.h"

SliderManip::SliderManip(int mode, QList <MyDevProperty *> &prop, PictureMode *pm, QImage* img, vector <unsigned short> &usData, QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(450);
    setMinimumHeight(310);
    move(0,0);
    setLeftPanel();
    initManipulators(mode, prop, pm, img, usData);
}

void SliderManip::turnOffHistogram(){
    emit hidehistogram();
}

void SliderManip::initBtHis(){
    btHis = new QPushButton("Histogram Off", this);
    btHis->move(width()-180, height()-20);
    btHis->resize(150, 20);
    connect(btHis, SIGNAL(clicked()), this, SLOT(turnOffHistogram()));
}

void SliderManip::setLeftPanel(){
    cbData= new QCheckBox(this);
    cbData->move(0,0);
    cbData->resize(80,16);
    cbData->setText("16Bit");
    cbAutoData= new QCheckBox(this);
    cbAutoData->move(0,16);
    cbAutoData->resize(80,20);
    cbAutoData->setText("Auto");
    cbAutoData->setChecked(false);
    refreshHis = new QPushButton(this);
    refreshHis->move(10,40);
    refreshHis->resize(80,20);
    refreshHis->setText("R");
    connect(refreshHis, SIGNAL(clicked()), this, SLOT(redrawHistogram()));
}

void SliderManip::setStartWidgetPosition(){
    histogram->setVisible(true);
    histogram->move(100,0);
    histogram->resize(350,190);
    histogram->plot->resize(350,190);
    bgcpl->move(0,215);
    rsfl->move(200,215);
}

SliderManip::~SliderManip(){
    delete bgcpl;
    delete rsfl;
    delete histogram;
    delete cbData;
    delete cbAutoData;
    delete refreshHis;
    delete btHis;
}

void SliderManip::recalcHistogram(){
    if (cbAutoData->isChecked())
        histogram->drawHistogram(*imgPointer);
}

void SliderManip::recalcHistogram16Bit(vector <unsigned short> data){
    if (cbAutoData->isChecked())
        histogram->drawHistogram(data);
}

void SliderManip::get16BitData(vector <unsigned short> data){
        histogram->drawHistogram(data);
}

void SliderManip::redrawHistogram(){
    if (!cbData->isChecked())
        histogram->drawHistogram(*imgPointer);
    else
        emit get16Bit();
}

void SliderManip::resizeEvent ( QResizeEvent * event ){
    histogram->resize(event->size().width()-100,event->size().height()-110);
    histogram->plot->resize(event->size().width()-100,event->size().height()-110);

    bgcpl->move(0,event->size().height()-100);
    rsfl->move(event->size().width()-200,event->size().height()-100);
    btHis->move(event->size().width()-180, event->size().height()-20);
}
void SliderManip::closeEvent (QCloseEvent *e){
    e->ignore();
}

void SliderManip::initManipulators(int mode,  QList <MyDevProperty *> &prop, PictureMode *pm, QImage* img, vector <unsigned short> &usData){
    imgPointer = img;
    curPicMode = mode;
    setWindowTitle("Manipulator");
    bgcpl = new BGCPL_WGT(mode, prop.at(BRIGHTNESS)->getValue().toInt() ,prop.at(CONTRAST)->getValue().toInt(),
                          this,prop.at(GAMMA)->getValue().toInt(), pm->getLBorder(), pm->getRBorder());
    rsfl = new RSFL_WGT(prop, this);
    rsfl->hFl->setChecked(prop.at(HOR_FLIP)->getValue().toBool());
    rsfl->vFl->setChecked(prop.at(VER_FLIP)->getValue().toBool());
    rsfl->setRotationVal(prop.at(ROTATION)->getValue().toInt());
    if(mode != IS_RGBIMG_COLOR){
        if (usData.size() != 0){
            histogram = new Histogrammm(usData, pm, this);
            cbData->setChecked(true);
        }
        else{
            histogram = new Histogrammm(*imgPointer, IS_8BITGREY_MODE, pm, this);
            cbData->setChecked(false);
        }
    }
    else {
        histogram = new Histogrammm(*imgPointer, IS_COLOR_MODE, pm,this);
        cbData->setChecked(false);
    }

    initBtHis();
    setStartWidgetPosition();
}

void SliderManip::changeDevice(int mode,  QList <MyDevProperty *> &prop, PictureMode *pm, QImage* img, vector <unsigned short> &usData ){
    delete bgcpl;
    delete rsfl;
    delete histogram;
    delete btHis;

    initManipulators(mode, prop, pm, img, usData);

    QResizeEvent event =  QResizeEvent(QSize(width(), height()),QSize(width(), height()));
    resizeEvent ( &event);
    rsfl->setVisible(true);
    bgcpl->setVisible(true);
    histogram->setVisible(true);
    btHis->setVisible(true);
}
