#include "manipulator.h"

Manipulator::Manipulator(int mode, QList <MyDevProperty *> &prop, PictureMode *pm, QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Manipulator");
    move (0,0);
    setFixedSize(400, 100);
    initObjects(mode, prop, pm);
}
Manipulator::~Manipulator(){
    delete bgcpl;
    delete rsfl;
    delete btHis;
}
void Manipulator::closeEvent (QCloseEvent *e){
    e->ignore();
}

void Manipulator::turnOnHistogram(){
    emit showhistogram();
}

void Manipulator::initObjects(int mode, QList <MyDevProperty *> &prop, PictureMode *pm){
    bgcpl = new BGCPL_WGT(mode,prop.at(BRIGHTNESS)->getValue().toInt(), prop.at(CONTRAST)->getValue().toInt(),
                          this, prop.at(GAMMA)->getValue().toInt(), pm->getLBorder(), pm->getRBorder());
    rsfl = new RSFL_WGT(prop, this);
    bgcpl->move(0,0);
    bgcpl->setVisible(true);
    rsfl->move(200, 0);
    rsfl->setVisible(true);

    btHis = new QPushButton("Histogram On", this);
    btHis->move(220, 80);
    btHis->resize(150, 20);
    connect(btHis, SIGNAL(clicked()), this, SLOT(turnOnHistogram()));
    btHis->setVisible(true);
}

void Manipulator::changeDevice(int mode, QList <MyDevProperty *> &prop, PictureMode *pm){
    delete bgcpl;
    delete rsfl;
    delete btHis;
    initObjects(mode, prop, pm);
}
