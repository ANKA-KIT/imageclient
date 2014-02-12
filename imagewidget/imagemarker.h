#ifndef IMAGEMARKER_H
#define IMAGEMARKER_H

#include <QColor>
#include <QMenu>
#include <QIcon>
#include <QPixmap>
#include <stdlib.h>
#include <time.h>

class RoiAction : public QMenu
{
    Q_OBJECT
public:
    QPoint p1;
    QPoint p2;
    QAction *actDel;
    QAction *actOpen;
    RoiAction(QPoint p1_, QPoint p2_, QWidget* parent):QMenu(parent){
        actOpen = new QAction(tr("Show ROI"), this);
        actDel = new QAction(tr("Delete ROI"), this);

        p1=p1_; p2=p2_;
        addAction(actOpen);
        addAction(actDel);
        setTitle("["+QString().number(p1.x())+","+QString().number(p1.y())+"];["+QString().number(p2.x())+","+QString().number(p2.y())+"]");
        connect(actOpen,SIGNAL(triggered()),this,SLOT(clicked()));
        connect(actDel,SIGNAL(triggered()),this,SLOT(del()));
    }
signals:
    void deleteRoi(RoiAction*);
    void actionClicked(RoiAction*);
public slots:
    void clicked(){
        emit actionClicked(this);
    }
    void del(){
        emit deleteRoi(this);
        deleteLater();
    }
};

class ImageMarker : public QMenu
{
    Q_OBJECT
public:
    explicit ImageMarker(int x, int y, QMenu *parent = 0);
    int _x;
    int _y;
    int _xOnPic;
    int _yOnPic;
    int xTransformed;
    int yTransformed;
    int visiableXPos;
    int visiableYPos;
    int _width;
    int hLineLength;
    int vLineLength;
    QRgb _clr;
    QPixmap *pic;
    QIcon *icon;

    QAction *actDel;
    QAction *editAction;
    QColor getColor() {
        return QColor(_clr);
    }
    void geometryChanged();

signals:
    void deleteMarker(ImageMarker *m);
    void colorChangedMarker(ImageMarker *m);
    void resizedMarker(ImageMarker *m);
    void geometryChangedMarker(ImageMarker *m);

public slots:
    void setMarkerColor(QRgb color);
    void del();
    void showEditMarkerDialog();
    void resizeMarker(int, int);
};


#endif // IMAGEMARKER_H
