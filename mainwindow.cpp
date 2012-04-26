/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QPainter>

//
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{

}

//Destructor of mainwindow
MainWindow::~MainWindow()
{
    fprintf(stderr,"---!_in mainwinDestructor\n");
//    delete subWin;
fprintf(stderr,"---!\n");
       delete setDevice;                 //set for current app tango device
        delete addNewDevice;              //set tango device in new app
        delete pushCommand;               //set tango command
        delete exitAct;                   //Stop app

        delete makeSnapshot;              //Make snapshot
        delete saveSnapshot;              //Save current snapshot
 //      delete scaleSnapshot;

    delete snapshot;
    delete server;

    delete area;
    fprintf(stderr,"---!\n");
 //   delete cmdTangoLine;
 //   delete tangoDev;
    delete ui;
    fprintf(stderr,"---!_Delete Mainwin in   destructor_!\n");
}

//Destructor of subwindow
SubWindow::~SubWindow(){
    delete device;
    delete img;
    delete wgt;
    delete scrollArea;
    fprintf(stderr,"---!_Delete SubWin in   destructor_!\n");

}

CommandLine::CommandLine(){}
TangoProperties::TangoProperties(){}

//on close mainwindow
void MainWindow::closeEvent ( QCloseEvent * closeEvent){
    subWin->setAttribute(Qt::WA_DeleteOnClose);
    if  (subWin[0].work){//subWin[0].isActiveWindow()){// isActiveWindow())//isHidden()
      subWin[0].close();
    }
    fprintf(stderr,"is_SubWin_ActiveWindow: %d\n", subWin[0].isActiveWindow());
    this->~MainWindow();        ///????????????????????????
    exit(0); /////////why app don't stop without this command?????????
}


void MainWindow::setTangoCommand(){
   // delete cmdTangoLine;
    cmdTangoLine = new CommandLine(this);
    cmdTangoLine->setWindowModality(Qt::ApplicationModal);
    QObject::connect(cmdTangoLine->btCancel, SIGNAL(clicked()), cmdTangoLine, SLOT(cancel()));
    QObject::connect(cmdTangoLine->btSend, SIGNAL(clicked()), this, SLOT(sendTangoCommandSLOT()));
    cmdTangoLine->show();
}

void MainWindow::sendTangoCommandSLOT(){
    sendTangoCommand(subWin[curDev].device, cmdTangoLine->tlCommand->text());
    cmdTangoLine->close();
    delete cmdTangoLine;
}

//start window Tango device property
void MainWindow::setTangoDevice(){ ///use one more slot!!!!!!
    tangoDeviceWin();
    QObject::connect(tangoDev->btChangeDevice, SIGNAL(clicked()), this, SLOT(changeDevice()));
    tangoDev->btNewDev->setEnabled(false);
    tangoDev->btChangeDevice->setEnabled(true);
}

void MainWindow::tangoDeviceWin(){
   // delete tangoDev;
    tangoDev = new TangoProperties(this);
    tangoDev->setWindowModality(Qt::ApplicationModal);
    QObject::connect(tangoDev->btCancel, SIGNAL(clicked()), tangoDev, SLOT(cancel()));
    tangoDev->show();
}
void MainWindow::setNewTangoDevice(){
    tangoDeviceWin();
    QObject::connect(tangoDev->btNewDev, SIGNAL(clicked()), this, SLOT(openDevInNewProc()));
    tangoDev->btChangeDevice->setEnabled(false);
    tangoDev->btNewDev->setEnabled(true);
}

//Set parent widget for subwindow
void SubWindow::setParent(MainWindow *p){
    parent = p;
}
void ImageWidget::setParent(MainWindow *p){
    parent = p;
}

//Constructor of main window
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    countDev = 0;   //const  1 realtime SubWin
    curDev = 0;     //const  1 realtime SubWin
    countImg = 0;
    curImg = 0;
    createActions();
    createMenu();
    subWin = new SubWindow();
    firstTime = true;
    ui->btScale->setEnabled(false);
    ui->btMkSnapshot->setEnabled(false);
    ui->btWriteImg->setEnabled(false);
    ui->btScaleRealTime->setEnabled(false);
    ui->btScaleSnapshot->setEnabled(false);

    QObject::connect(subWin,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
                     subWin,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates)));

    QStringList ls;
    ls  <<"QImage::Format_Indexed8"
        <<"QImage::Format_RGB32"
        <<"QImage::Format_ARGB32"
        <<"QImage::Format_ARGB32_Premultiplied"
        <<"QImage::Format_RGB16"
        <<"QImage::Format_ARGB8565_Premultiplied"
        <<"QImage::Format_RGB666"
        <<"QImage::Format_ARGB6666_Premultiplied"
        <<"QImage::Format_RGB555"
        <<"QImage::Format_ARGB8555_Premultiplied"
        <<"QImage::Format_RGB888"
        <<"QImage::Format_RGB444"
        <<"QImage::Format_ARGB4444_Premultiplied";
    colorFormat = "QImage::Format_RGB32";
    intColorFormat = QImage::Format_RGB32;//4;
    delim = 4;
    ui->cmbColorFormat->addItems(ls);
    ui->cmbColorFormat->setCurrentIndex(1); //value QImage::Format_RGB32
    QObject::connect(ui->cmbColorFormat, SIGNAL(currentIndexChanged(int)), this, SLOT(changeColorFormat(int)));
    tangoDev = new TangoProperties(this);
    cmdTangoLine = new CommandLine(this);
}

//Constructor of subwindow  //overloaded
SubWindow::SubWindow(QWidget *parent, Qt::WindowFlags flags)
{
    device = new  Tango::DeviceProxy();
    wgt = new ImageWidget();
    scrollArea = new QScrollArea();
    img = new QImage();

    scrollArea->hide();
    scrollArea->setWindowModality(Qt::WindowModal);
    scrollArea->resize(800, 500);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->move(50, 100);
    wgt->setAutoFillBackground(true);
    wgt->setMouseTracking(true);
    this->setAutoFillBackground(true);

    QObject::connect(this,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),this,
    SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}

void MainWindow::sendTangoCommand(Tango::DeviceProxy *device, QString command){
    try{
            device->command_inout(command.toAscii().constData());
    }
    catch(Tango::ConnectionFailed){
          fprintf(stderr, "ConnectionFailed while send tango command to %s\n", subWin[curDev].device->name().c_str());
          exit(1);
    }
    catch(Tango::WrongData){
          fprintf(stderr, "Wrong Data while send tango command to %s\n", subWin[curDev].device->name().c_str());
          exit(1);
    }
    catch(Tango::DevFailed){
         fprintf(stderr, "DevFailed while send tango command to %s", subWin[curDev].device->name().c_str());
         exit(1);
    }
}

//On Subwindow state changing
void SubWindow::handleWindowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState){
    if(newState == Qt::WindowActive){
        int i;
        int wins = parent->countDev+1;
        bool found = false;
        fprintf(stderr,"SubWindow>>   newState == Qt::WindowActive\n");
        for (i = 0; i<wins; i++){

            if (this == &parent->subWin[i]){
                    parent->curDev = i;
                    parent->ui->lbCurWin->setText(QString("CurWin_") + QString(i+49));
                    found = true;
                    break;
            }
        }

        if (!found){
            for (i = 0; i<parent->listSnap.size(); i++){
                 if(this == parent->listSnap.at(i)){
                    parent->curImg = i;
                    parent->ui->lbCurWin->setText(QString("CurSnap_") + QString(i+49));
                    parent->subWinSnapPointer = this;
                    parent->ui->btScale->setEnabled(true);
                    parent->ui->btWriteImg->setEnabled(true);
                    parent->saveSnapshot->setEnabled(true);
                    parent->ui->btScaleSnapshot->setEnabled(true);
                    parent->snapshot->setEnabled(true);

                   // QObject::connect(parent->saveSnapshot, SIGNAL(triggered()), this, SLOT(saveImg()));
                    break;
                }
            }
        }
    }
    if(newState == Qt::WindowMinimized){
        fprintf(stderr,"Subwindow is minimaized\n");
        this->resize(50, 15);
    }
    if(oldState == Qt::WindowActive && isSnapshot){
        //this->disconnect(parent->saveSnapshot);
    }
}

//on change size of main window
void MainWindow::resizeEvent( QResizeEvent *e ){
    area->resize(e->size());
}

//on mouse press event at picture widget
void ImageWidget::mousePressEvent ( QMouseEvent * e){
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    parent->ui->lbLastMouse->setText(QString("Last Mouse Pos: (") +
                                     QString().setNum(lastMouseX) + QString(";") + QString().setNum(lastMouseY) + QString(")") );
    fprintf(stderr, "ImageWidget::mousePressEvent\n");
}

////on mouse move event at picture widget
void ImageWidget::mouseMoveEvent ( QMouseEvent * e){
    mouseX = e->x();
    mouseY = e->y();
    parent->ui->lbCurMouse->setText(QString("Current Mouse Pos: (") +
                                    QString().setNum(mouseX) + QString(";") + QString().setNum(mouseY) + QString(")") );
    repaint();

    fprintf(stderr, "ImageWidget::mouseMoveEvent\n");
}

//on paint event
void ImageWidget::paintEvent( QPaintEvent * e){
    QPainter p(this);
    p.setPen(QPen(Qt::yellow, 2));
    p.drawLine(0, mouseY, this->width(), mouseY);
    p.drawLine(mouseX, 0, mouseX, this->height());
    fprintf(stderr, "ImageWidget::paintEvent\n");
}

//on close subwindow
void SubWindow::closeEvent ( QCloseEvent * closeEvent ){
    fprintf(stderr, "Del subWin\n");
    if (!isSnapshot){
        work = false;  //stop reading tango device       //it is not delete realtime subwindow!!!!!!OK!!!!!!!
        fprintf(stderr, "Work is %d\n", isSnapshot);
        parent->ui->btChangeDevice->setEnabled(true);
        parent->ui->btMkSnapshot->setEnabled(false);

        parent->makeSnapshot->setEnabled(false);
        parent->ui->btScaleRealTime->setEnabled(false);
        parent->setDevice->setEnabled(true);
        parent->pushCommand->setEnabled(false);

    }
    else{
        QList<SubWindow*>::iterator iter;
        for (iter = parent->listSnap.begin(); iter < parent->listSnap.end(); ++iter){

             if(this == *iter){
                parent->subWinSnapPointer = NULL;
                fprintf(stderr,"!Delete a Snapshot!\n");
                qDeleteAll(iter, iter);                      ////current point??>>>>>
                parent->listSnap.erase(iter);
                parent->ui->btScale->setEnabled(false);
                parent->ui->btWriteImg->setEnabled(false);
                parent->saveSnapshot->setEnabled(false);

                parent->ui->btScaleSnapshot->setEnabled(false);
                break;
            }
        }
    }
}

void MainWindow::changeColorFormat(int format){
    intColorFormat = format+3;
    switch(intColorFormat){
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
        delim = 4; break;
    case QImage::Format_RGB666:
    case QImage::Format_ARGB6666_Premultiplied:
    case QImage::Format_ARGB8555_Premultiplied:
    case QImage::Format_RGB888:
    case QImage::Format_ARGB8565_Premultiplied:
        delim = 3; break;
    case QImage::Format_RGB16:
    case QImage::Format_RGB555:
    case QImage::Format_RGB444:
    case QImage::Format_ARGB4444_Premultiplied:
        delim = 2; break;
    case QImage::Format_Indexed8:
        delim = 1; break;
    }
}

//open new device
void MainWindow::openDevInNewProc(){
    QProcess::startDetached("./TestApp",
                            QStringList() << this->tangoDev->tlServer->text()
                                << this->tangoDev->tlDevice->text()
                                << this->tangoDev->tlAttr->text(), "./");
    tangoDev->close();
    delete tangoDev;
}
