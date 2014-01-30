#ifndef ROISUBWINDOW_H
#define ROISUBWINDOW_H

#include <subwindowmdi.h>
#include <roiclass.h>

class RoiSubWindow : public SubWindow
{
    Q_OBJECT
    QString _serverName;
    QString _serverAttr;
public:
    RoiSubWindow():SubWindow(0){}
    RoiSubWindow(QPoint, QPoint,TImage *);
    QAction *snpWhole ;
    QAction *snpVis;
    QAction *setRoi;
    ROIClass *roi;
public slots:
    void changeRoi();
    void changeRoi(QPoint,QPoint);
};

#endif // ROISUBWINDOW_H
