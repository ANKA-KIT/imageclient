#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGroupBox>
#include <QLabel>

#include "config.h"
#include "syncdialog.h"

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
    StartTangoWindow *startTWin;
    startTWin = new StartTangoWindow();
    startTWin->setAttribute(Qt::WA_DeleteOnClose);
    connect(startTWin, SIGNAL(dev(QString, QString)), this, SLOT(initRealtime(QString, QString)));
    startTWin->show();
}

void MainWindow::variablesWindow()
{
    if (rtContainer->getRealtimeLastVal() == -1) {
        return;
    }
    TangoServerVariablesWin *varWin;
    RealtimeSubWindow *rt = rtContainer->getRealtimeCurWin();
    varWin = new TangoServerVariablesWin(rt->tim->getServerName());
    varWin->setAttribute(Qt::WA_DeleteOnClose);
    connect(varWin, SIGNAL(setVar(QString)), rt, SLOT(setServerVar(QString)));
    varWin->show();
}

void MainWindow::syncDialog()
{
    SyncDialog sync(this);
    sync.exec();
}

void MainWindow::initRealtime(QString dev, QString attr){
    RealtimeSubWindow *rt = new RealtimeSubWindow(dev, attr);
    rt->setAttribute(Qt::WA_DeleteOnClose);
    rtContainer->add(rt);
    connect(rt->snpWhole,SIGNAL(triggered()),this,SLOT(makeSnpWhole()));
    connect(rt->snpVis,SIGNAL(triggered()),this,SLOT(makeSnpVis()));
    connect(rt, SIGNAL(winChanged(SubWindow*)),rtContainer,SLOT(realtimeChanged(SubWindow*)));
    connect(rt, SIGNAL(destroyed(QObject*)), rtContainer, SLOT(onCloseRaltime(QObject*)));
    connect(rt, SIGNAL(newRoiCreated(QPoint,QPoint,TImage*)), this, SLOT(initRoi(QPoint,QPoint,TImage*)));
    area->addSubWindow(rt);
    rt->show();
}

void MainWindow::initSnapshot(TImage *tim, int type){
    SnapshotSubWindow *snp = new SnapshotSubWindow(tim, type);
    snp->setAttribute(Qt::WA_DeleteOnClose);
    snpContainer->add(snp);
    connect(snp, SIGNAL(destroyed(QObject*)), snpContainer, SLOT(onCloseSnapshot(QObject*)));
    connect(snp, SIGNAL(winChanged(SubWindow*)),snpContainer,SLOT(snapshotChanged(SubWindow*)));
//    connect(snp->snp, SIGNAL(mousePosition(QPoint)), this, SLOT(curPosition(QPoint)));
//    connect(snp->snp, SIGNAL(greyscaleImageColor(int)), this, SLOT(curColor(int)));
//    connect(snp->snp, SIGNAL(rgbImageColor(int,int,int)), this, SLOT(curColor(int,int,int)));
    area->addSubWindow(snp);
    snp->show();
}

void MainWindow::initRoi(QPoint p1,QPoint p2,TImage *tim){
    RoiSubWindow *roi = new RoiSubWindow(p1,p2,tim);
    roi->setAttribute(Qt::WA_DeleteOnClose);
    roiContainer->add(roi);
    connect(roi->snpWhole,SIGNAL(triggered()),this,SLOT(makeSnpWhole()));
    connect(roi->snpVis,SIGNAL(triggered()),this,SLOT(makeSnpVis()));
    connect(roi, SIGNAL(destroyed(QObject*)), roiContainer, SLOT(onCloseRoi(QObject*)));
    connect(roi, SIGNAL(winChanged(SubWindow*)),roiContainer,SLOT(roiChanged(SubWindow*)));
//    connect(roi->roi->sample, SIGNAL(mousePosition(QPoint)), this, SLOT(curPosition(QPoint)));
//    connect(roi->roi->sample, SIGNAL(greyscaleImageColor(int)), this, SLOT(curColor(int)));
//    connect(roi->roi->sample, SIGNAL(rgbImageColor(int,int,int)), this, SLOT(curColor(int,int,int)));
    area->addSubWindow(roi);
    roi->show();
}

void MainWindow::makeSnpWhole()
{
    if (rtContainer->getRealtimeLastVal() !=-1)
        initSnapshot(rtContainer->getRealtimeLastImage(), SnapshotSubWindow::WHOLE);
}
void MainWindow::makeSnpVis()
{
    if (rtContainer->getRealtimeLastVal() !=-1)
        initSnapshot(rtContainer->getRealtimeLastImage(), SnapshotSubWindow::VISIABLE);
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
