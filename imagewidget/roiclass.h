#ifndef ROICLIASS_H
#define ROICLIASS_H

#include "TImageSnapshot"
#include "TImage"

class ROIClass : public QWidget//TImageSnapshot
{
    Q_OBJECT
private:
    bool doubleMarker;
    TImage *ptr;
public:
    int maxWidth;
    int maxHeight;
    TImageSnapshot *sample;
    ROIClass(TImage *, QWidget *p, QRect);
    QPoint offset;
    QPoint size;

    //void setImage(QImage img );
signals:
    void roiMarker(QPoint, QRgb);
public slots:
    void setRect(QPoint p1, QPoint p2);
    void onNewFrame(QImage);
    void sendMarker(QPoint, QRgb);
    void realtimeMarkerInited(QPoint, QRgb);

    void realtimeMarkerDeleted(QPoint p, QRgb col);
    void realtimeMarkerColorChanged(QPoint p, QRgb col);
};

#endif // ROICLIASS_H
