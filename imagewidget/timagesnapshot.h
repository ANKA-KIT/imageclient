#ifndef TIMAGESNAPSHOT_H
#define TIMAGESNAPSHOT_H

//My_Code
#include "eimagebase.h"

class TImageSnapshot : public EImageBase//, public QTangoWidgetCommon
{
    Q_OBJECT
private:
    void resizeEvent(QResizeEvent *);
public:
    TImageSnapshot(QWidget *p);
    TImageSnapshot(QImage , int , int , int , QWidget *p);
    TImageSnapshot(QVector<unsigned short > vector, int x, int y, int pm, QWidget *p);

public slots:
    void setImage(QImage img );
    void showParams();

};


#endif // TIMAGESNAPSHOT_H
