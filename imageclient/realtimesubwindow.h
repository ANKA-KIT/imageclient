#ifndef REALTIMESUBWINDOW_H
#define REALTIMESUBWINDOW_H

#include <subwindowmdi.h>
#include <tangoservervariableswin.h>

class TImage;
class RoiAction;
class SyncDialog;

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
    RealtimeSubWindow(QString device, QString attribute);
    void setServerModeRead(bool val);
    void setServerModeWrite(bool val);
    void setClientSideMode(bool val);
private:
    SyncDialog* syncDialog;

signals:
    void newRoiCreated(QPoint,QPoint,TImage*);
public slots:
    void setServerVar(QString val);

    void initRoi();
    void initRoi(QPoint p1,QPoint p2);
    void showRoi(RoiAction *r);
    void addRoi(RoiAction *r);

    void onChangeFullscreen(bool);
};

#endif // REALTIMESUBWINDOW_H
