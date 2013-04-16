#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QHBoxLayout>
#include <starttangowin.h>
#include <tangoservervariableswin.h>
#include <realtimecontainer.h>
#include <snapshotcontainer.h>
#include <roicontainer.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString emptyIcon;
public:


    QString trueIcon,falseIcon;
    explicit MainWindow(QWidget *parent = 0);
    QMdiArea *area;
    RealtimeContainer *rtContainer;
    SnapshotContainer *snpContainer;
    RoiContainer *roiContainer;
    QLabel *lbPos;
    QLabel *lbColor;
    ~MainWindow();
private:
    Ui::MainWindow *ui;
public slots:
    void startWindow();
    void variablesWindow();
    void initRealtime(QString dev, QString attr);
    void initSnapshot(TImage *tim, int type);
    void initRoi(QPoint, QPoint, TImage *);
    void makeSnpVis();
    void makeSnpWhole();
    void curPosition(QPoint);
    void curColor(int);
    void curColor(int,int,int);

};

#endif // MAINWINDOW_H
