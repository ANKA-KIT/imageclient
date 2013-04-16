#ifndef IMAGEMARKER_H
#define IMAGEMARKER_H

#include <QColor>
#include <QMenu>
#include <QMenu>
#include <QIcon>
#include <QPen>
#include <QPainter>
#include <QPixmap>
#include <QColorDialog>
#include <stdlib.h>
#include <time.h>

class RoiAction : public QMenu//QAction{
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
    }// actNew = menuAction();}
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

class ImageMarker : public QMenu//QAction//QObject
{
    Q_OBJECT
public:
    explicit ImageMarker(int x, int y, QMenu *parent = 0);
    //QAction *act;
    int _x;
    int _y;
    int _xOnPic;
    int _yOnPic;
    int xTransformed;
    int yTransformed;
    int visiableXPos,visiableYPos;
    int _width;
    int hLineLength;
    int vLineLength;
    QRgb _clr;
    QPixmap *pic;
    QIcon *icon;

    QAction *actDel;
    QAction *actSettings;
signals:
    void deleteMarker(ImageMarker*);
    void colorChangedMarker(ImageMarker*);
public slots:
    void setMarkerColor(QRgb color);
    void del();
    void showSettings();
};


#endif // IMAGEMARKER_H
