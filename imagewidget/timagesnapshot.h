#ifndef TIMAGESNAPSHOT_H
#define TIMAGESNAPSHOT_H

#include "eimagebase.h"

class TImageSnapshot : public EImageBase
{
    Q_OBJECT
private:
    void resizeEvent(QResizeEvent *);
public:
    TImageSnapshot(QWidget *p);
    TImageSnapshot(QImage, int dimX, int dimY, int pictureMode, QWidget *p);
    TImageSnapshot(QVector<unsigned short > vector, int x, int y, int pictureMode, QWidget *p);

public slots:
    void setImage(QImage img );
    void showParams();

};


#endif // TIMAGESNAPSHOT_H
