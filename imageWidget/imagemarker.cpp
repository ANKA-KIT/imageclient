#include "imagemarker.h"

ImageMarker::ImageMarker(int x, int y, QMenu *parent) :
    QMenu(parent)
{
    _xOnPic = xTransformed = _x = x;
    _yOnPic = yTransformed = _y = y;
    hLineLength = vLineLength = 5;
    srand (time(NULL));
    int r = rand()%255;
    int g = rand()%255;
    int b = rand()%255;
    _clr = qRgb(r,g,b);
    pic = new QPixmap(48,48);
    pic->fill(QColor(_clr));
    setTitle("Marker["+QString().number(x)+";"+QString().number(y)+"]");
    _width = 1;

    actDel = new QAction(tr("Delete"),this);
    actSettings = new QAction(tr("Marker Color"),this);
    connect(actDel,SIGNAL(triggered()),this,SLOT(del()));
    connect(actSettings,SIGNAL(triggered()),this,SLOT(showSettings()));

    menuAction()->setIcon(*pic);
    menuAction()->setIconVisibleInMenu(true);

    this->addAction(actSettings);
    this->addAction(actDel);
}

void ImageMarker::del(){
    emit deleteMarker(this);
    deleteLater();
}

void ImageMarker::showSettings(){
    QColor color;
    color = QColorDialog::getColor(color, this);
    setMarkerColor(color.rgb());
}

void ImageMarker::setMarkerColor(QRgb color){
    _clr = color;
    pic->fill(QColor(_clr));
    menuAction()->setIcon(*pic);
    emit colorChangedMarker(this);
}
