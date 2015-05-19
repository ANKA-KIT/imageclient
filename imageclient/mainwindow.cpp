#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "snapshotsubwindow.h"

#include <QGroupBox>
#include <QLabel>

#include "config.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    startImageMode  = -1;
    startDelayTime = -1;

    emptyIcon = "/icons/true.png";
    trueIcon = ":/icons/true.png";
    falseIcon = ":/icons/false.png";
    ui->setupUi(this);

    rtContainer = new RealtimeContainer(this);
    snpContainer = new SnapshotContainer(this);
    roiContainer = new RoiContainer(this);

    ui->menuRealtime->addMenu(rtContainer->serverMode);
    ui->menuRealtime->addAction(rtContainer->actClientSide);
    QVBoxLayout *vbox = new QVBoxLayout(centralWidget());
    vbox->setMargin(0);
    area = new QMdiArea(this);
    area->setGeometry(0, 0, 400, 300);
    QHBoxLayout *layout = new QHBoxLayout;
    lbPos = new QLabel(this);
    layout->addWidget(lbPos);
    lbColor = new QLabel(this);
    layout->addWidget(lbColor);
    layout->addStretch();
    vbox->addStretch();
    vbox->addLayout(layout);
    vbox->addStretch();
    vbox->addWidget(area, 100);

    QString title = "ImageClient ";
    title += VERSION;
    setWindowTitle(title);
}

void MainWindow::chooseDevice()
{
    startTWin = new StartTangoWindow();
    startTWin->setAttribute(Qt::WA_DeleteOnClose);
    connect(startTWin, SIGNAL(dev(QString, QString)), this, SLOT(initRealtime(QString, QString)));
    startTWin->show();
}

void MainWindow::variablesWindow()
{
    if (!rtContainer->getRealtimeLastWin()) {
        return;
    }
    TangoServerVariablesWin *varWin;
    RealtimeSubWindow *rt = rtContainer->getRealtimeLastWin();
    varWin = new TangoServerVariablesWin(rt->tim->getServerName());
    varWin->setAttribute(Qt::WA_DeleteOnClose);
    connect(varWin, SIGNAL(setVar(QString)), rt, SLOT(setServerVar(QString)));
    varWin->show();
}

void MainWindow::initRealtime(QString dev, QString attr){
    RealtimeSubWindow *rt = new RealtimeSubWindow(dev, attr);
    rt->setAttribute(Qt::WA_DeleteOnClose);
    connect(rt->snpWhole,SIGNAL(triggered()),this,SLOT(makeSnpWhole()));
    connect(rt->snpVis,SIGNAL(triggered()),this,SLOT(makeSnpVis()));
    connect(rt, SIGNAL(activated(SubWindow*)), rtContainer, SLOT(windowActivated(SubWindow*)));
    connect(rt, SIGNAL(deactivated(SubWindow*)), rtContainer, SLOT(windowDeactivated(SubWindow*)));
    connect(rt, SIGNAL(destroyed(QObject*)), rtContainer, SLOT(onCloseRaltime(QObject*)));
    connect(rt, SIGNAL(newRoiCreated(QPoint,QPoint,TImage*)), this, SLOT(initRoi(QPoint,QPoint,TImage*)));
    area->addSubWindow(rt);
    rt->show();
}

void MainWindow::initSnapshot(TImage *tim, int type){
    SnapshotSubWindow *snp = new SnapshotSubWindow(tim, type);
    snp->setAttribute(Qt::WA_DeleteOnClose);
    connect(snp, SIGNAL(activated(SubWindow*)), snpContainer, SLOT(windowActivated(SubWindow*)));
    connect(snp, SIGNAL(deactivated(SubWindow*)), snpContainer, SLOT(windowDeactivated(SubWindow*)));
    connect(snp, SIGNAL(destroyed(QObject*)), snpContainer, SLOT(onCloseSnapshot(QObject*)));
    area->addSubWindow(snp);
    snp->show();
}

void MainWindow::initRoi(QPoint p1,QPoint p2,TImage *tim){
    RoiSubWindow *roi = new RoiSubWindow(p1,p2,tim);
    roi->setAttribute(Qt::WA_DeleteOnClose);
    roiContainer->add(roi);
    connect(roi->snpWhole, SIGNAL(triggered()), this, SLOT(makeSnpWhole()));
    connect(roi->snpVis, SIGNAL(triggered()), this, SLOT(makeSnpVis()));
    connect(roi, SIGNAL(destroyed(QObject*)), roiContainer, SLOT(onCloseRoi(QObject*)));
    connect(roi, SIGNAL(winChanged(SubWindow*)), roiContainer, SLOT(roiChanged(SubWindow*)));
    area->addSubWindow(roi);
    roi->show();
}

void MainWindow::makeSnpWhole()
{
    if (rtContainer->getRealtimeLastWin()) {
        initSnapshot(rtContainer->getRealtimeLastImage(), SnapshotSubWindow::WHOLE);
    }
}
void MainWindow::makeSnpVis()
{
    if (rtContainer->getRealtimeLastWin()) {
        initSnapshot(rtContainer->getRealtimeLastImage(), SnapshotSubWindow::VISIBLE);
    }
}

void MainWindow::curPosition(QPoint p){
    lbPos->setText("["+ QString().number(p.x())+"]:["+QString().number(p.y())+"]");
}

void MainWindow::curColor(int cl){
    lbColor->setText("Color: (" + QString().number(cl) + ")");
}

void MainWindow::curColor(int r, int g, int b){
    lbColor->setText("Color: (" + QString().number(r) + "," + QString().number(g) + ","
                     + QString().number(b) + ")");
}
MainWindow::~MainWindow()
{
    delete ui;
}
