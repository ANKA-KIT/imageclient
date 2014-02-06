#ifndef REALTIMESUBWINDOW_H
#define REALTIMESUBWINDOW_H

#include <subwindowmdi.h>
#include <TImage>
#include <tangoservervariableswin.h>
#include <QVBoxLayout>

class RealtimeSubWindow : public SubWindow
{
    Q_OBJECT

    bool initRoiFlag;
public:
    TImage *tim;
    QAction *snpWhole ;
    QAction *snpVis;
    QAction *newRoi;

    QMenu *roiMenu;
    RealtimeSubWindow(QString, QString );
    void setServerModeRead(bool val);
    void setServerModeWrite(bool val);
    void setClientSideMode(bool val);
signals:
    void newRoiCreated(QPoint,QPoint,TImage*);
public slots:
    void setServerVar(QString val);

    void initRoi();
    void initRoi(QPoint p1,QPoint p2);
    void showRoi(RoiAction*);
    void addRoi(RoiAction *r);

    void onChangeFullscreen(bool);
};

#endif // REALTIMESUBWINDOW_H
