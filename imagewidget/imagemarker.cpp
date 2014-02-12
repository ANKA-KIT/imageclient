#include "imagemarker.h"

ImageMarker::ImageMarker(int x, int y, QMenu *parent) :
    QMenu(parent)
{
    _xOnPic = xTransformed = _x = x;
    _yOnPic = yTransformed = _y = y;
    hLineLength = vLineLength = 5;
    srand (time(NULL));
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    _clr = qRgb(r, g, b);
    pic = new QPixmap(48, 48);
    pic->fill(QColor(_clr));
    setTitle("Marker[" + QString().number(x) + ";" + QString().number(y) + "]");
    _width = 1;

    actDel = new QAction(tr("Delete"), this);
    actSettings = new QAction(tr("Marker Color"), this);
    connect(actDel, SIGNAL(triggered()), this, SLOT(del()));
    connect(actSettings, SIGNAL(triggered()), this, SLOT(showSettings()));

    actSize = new QAction(tr("Marker Size"), this);
    connect(actSize, SIGNAL(triggered()), this, SLOT(resizeMarkerWin()));

    menuAction()->setIcon(*pic);
    menuAction()->setIconVisibleInMenu(true);

    this->addAction(actSettings);
    this->addAction(actSize);
    this->addAction(actDel);
}

void ImageMarker::del()
{
    emit deleteMarker(this);
    deleteLater();
}

void ImageMarker::showSettings()
{
    QColor color;
    color = QColorDialog::getColor(color, this);
    setMarkerColor(color.rgb());
}

void ImageMarker::setMarkerColor(QRgb color)
{
    _clr = color;
    pic->fill(QColor(_clr));
    menuAction()->setIcon(*pic);
    emit colorChangedMarker(this);
}

void ImageMarker::resizeMarkerWin()
{
    ResizeMarker *sizeWin = new ResizeMarker();
    connect(sizeWin, SIGNAL(changeMarkerSize(int,int)), this, SLOT(resizeMarker(int,int)));
    sizeWin->show();
}

void ImageMarker::resizeMarker(int h,int v){
    hLineLength = h;
    vLineLength = v;
}

ResizeMarker::ResizeMarker(){
    setAttribute(Qt::WA_DeleteOnClose);
    QHBoxLayout *h = new QHBoxLayout;
    hor = new QLineEdit(this);
    ver = new QLineEdit(this);
    QLabel *lb = new QLabel("Marker length", this);
    h->addWidget(lb);
    h->addWidget(hor);
    h->addWidget(ver);
    QFormLayout *layout = new QFormLayout(this);
    layout->addRow(h);
    QPushButton *bt = new QPushButton("Ok",this);
    layout->addRow(bt);
    connect(bt, SIGNAL(clicked()), this, SLOT(onOk()));
    resize(300,100);
}

void ResizeMarker::onOk(){
    bool h,v;
    int hVal = hor->text().toInt(&h);
    int vVal = ver->text().toInt(&v);
    if (h && v){
        emit changeMarkerSize(hVal, vVal);
        deleteLater();
    }
}
