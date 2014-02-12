#include "imagemarker.h"

#include "editmarkerdialog.h"

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
    connect(actDel, SIGNAL(triggered()), this, SLOT(del()));

    editAction = new QAction(tr("Edit"), this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(showEditMarkerDialog()));

    menuAction()->setIcon(*pic);
    menuAction()->setIconVisibleInMenu(true);

    this->addAction(editAction);
    this->addAction(actDel);
}

void ImageMarker::del()
{
    emit deleteMarker(this);
    deleteLater();
}

void ImageMarker::geometryChanged()
{
    emit geometryChangedMarker(this);
}

void ImageMarker::setMarkerColor(QRgb color)
{
    _clr = color;
    pic->fill(QColor(_clr));
    menuAction()->setIcon(*pic);
    emit colorChangedMarker(this);
}

void ImageMarker::showEditMarkerDialog()
{
    EditMarkerDialog *editDialog = new EditMarkerDialog(this);
    editDialog->exec();
    delete editDialog;
}

void ImageMarker::resizeMarker(int h, int v)
{
    hLineLength = h;
    vLineLength = v;
    emit resizedMarker(this);
}
