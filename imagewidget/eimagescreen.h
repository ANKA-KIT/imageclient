#ifndef EIMAGESCREEN_H
#define EIMAGESCREEN_H

#include <QWidget>
#include <QImage>
#include <QMenu>
#include <QWheelEvent>
#include <QScrollBar>
#include <math.h>

class ImageMarker;

struct TransformParametres {
    bool horFlip;
    bool verFlip;
    double rotate;
    bool fullPictureMode;
    double imageScale;
};

class EImageScreen : public QWidget
{
     Q_OBJECT
private:
    bool lButtonPresed;
    int curXPos;
    int curYPos;
    bool isPi2rotated;

public:
    QImage setTransformPropertiesOnImg(QImage img);
    TransformParametres imageTransform;
    int _curMouseX,_curMouseY;
    int limX1, limX2, limY1, limY2;
    int moveX;
    int moveY;
    QMenu *contextMenu;

    double sclX;
    double sclY;
    QList<ImageMarker *> marker;
    QImage image;
    int picW,picH;
    EImageScreen(QWidget *p);
    void ShowContextMenu(const QPoint& pos);
    void setActionMenu(QList<QAction *> acts);
    ImageMarker *initMarker(QPoint pos);

    void setMarkersOnPic(bool, QImage &imgPtr);
    double getRotate();
    QPoint convertToImageCoordinates();

    QScrollBar *heightScrBar;
    QScrollBar *widthScrBar;

signals:
    void moveXSignal(int);
    void currentPos(int,int);
    void moveYSignal(int);
    void rightClickPos(QPoint);
    void chScaleByWheel(double);
    void imgTransformed(QImage);
    void imgChanged(QImage);

    void showPictureSize(int,int,int,int);
    void repainting();

    void mousePosition(QPoint);
    void newMarker(ImageMarker *m);
    void delMarker(QPoint, QRgb);
    void colorChMarker(QPoint, QRgb);
    void markerColorChanged(ImageMarker *m);

public slots:
    void rescreen();
    void setPi2Rotated(bool);
    void setPicWH(int,int);

    void setMoveX(int val);
    void setMoveY(int val);
    void chMoveXOn(int val);
    void chMoveYOn(int val);
    void drawing(QImage &img);
    void setFullscreenMode(bool val);
    void chScaleVal(double val);
    void setScale(double val);
    void initMarker();
    QPoint convertToImagePoint(int x, int y);
    QImage setImageByFullScreenMode(QImage);

    QImage chScale(QImage &image, double val);
    QImage chScale(QImage &image, double valX, double valY);
    QImage chVerFlip(QImage &image);
    QImage chHorFlip(QImage &image);
    QImage changeRotateImg(QImage &image, int val);

    void recalcMarkerPos();
    void setRotate(double);
    void setHFlip(bool);
    void setVFlip(bool);

protected slots:
    void setLimits(int,int,int,int);

    void onMarkerDelete(ImageMarker *m);
    void onMarkerColorChanged(ImageMarker* p);
    void paintEvent( QPaintEvent * e);
    void setCursorPos( int x, int y);
    virtual QMenu* rightClickMenu() { return contextMenu; }

    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * e);
    void mouseReleaseEvent ( QMouseEvent * event );
};

#endif // EIMAGESCREEN_H
