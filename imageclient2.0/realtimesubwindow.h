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
    //ServerVariables *serVars;
    TImage *tim;
    QAction *snpWhole ;
    QAction *snpVis;
    QAction *newRoi;

    QMenu *roiMenu;
    RealtimeSubWindow(QString, QString );//, QMdiSubWindow*parent);
    void setServerModeRead(bool val);
    void setServerModeWrite(bool val);
    void setClientSideMode(bool val);
signals:
    void newRoiCreated(QPoint,QPoint,TImage*);
public slots:
    void setServerVar(QString val);//(ServerVariables );

    void initRoi();
    void initRoi(QPoint p1,QPoint p2);
    void showRoi(RoiAction*);
    void addRoi(RoiAction *r);
};

#endif // REALTIMESUBWINDOW_H
