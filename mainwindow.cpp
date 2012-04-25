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
    delete subWin;
    delete area;
    delete ui;
}

void CommandLine::cancel(){
    this->close();
}

void TangoProperties::cancel(){
    this->close();
}

CommandLine::~CommandLine(){
    delete lbCommand;
    delete tlCommand;
    delete btSend;
    delete btCancel;
}

//Destructor of subwindow
SubWindow::~SubWindow(){
//    delete attr;
    delete device;
    delete img;
    delete wgt;
    delete scrollArea;
    fprintf(stderr,"\n!_Delete SubWin in   destructor_!");
}

//Destructor of TangoProperties
TangoProperties::~TangoProperties(){
    delete tlAttr;
    delete tlDevice;
    delete tlServer;
    delete lbServer;
    delete lbDevice;
    delete lbAttr;
    delete centralWidget;
}

//on close mainwindow
void MainWindow::closeEvent ( QCloseEvent * closeEvent){
    if  (subWin[0].isActiveWindow())
      subWin[0].close();
}


void MainWindow::setTangoCommand(){
    cmdTangoLine = new CommandLine(this);
    cmdTangoLine->setWindowModality(Qt::ApplicationModal);
    QObject::connect(cmdTangoLine->btCancel, SIGNAL(clicked()), cmdTangoLine, SLOT(cancel()));
    QObject::connect(cmdTangoLine->btSend, SIGNAL(clicked()), this, SLOT(sendTangoCommand()));
    cmdTangoLine->show();
}

//start window Tango device property
void MainWindow::setTangoDevice(){ ///use one more slot!!!!!!
    tangoDev = new TangoProperties(this);
    tangoDev->setWindowModality(Qt::ApplicationModal);
    QObject::connect(tangoDev->btCancel, SIGNAL(clicked()), tangoDev, SLOT(cancel()));
    QObject::connect(tangoDev->btNewDev, SIGNAL(clicked()), this, SLOT(openDevInNewProc()));
    QObject::connect(tangoDev->btChangeDevice, SIGNAL(clicked()), this, SLOT(changeDevice()));
    tangoDev->show();
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
}

//Constructor of subwindow  //overloaded
SubWindow::SubWindow(QWidget *parent, Qt::WindowFlags flags)
{
 //   attr = new Tango::DeviceAttribute();

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

//Constructor of CommandLine
CommandLine::CommandLine(MainWindow *main){
    CommandLine *MainWind = this;
    parent = main;
    centralWidget = new QWidget(MainWind);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(300, 50);
    this->move(100,100);
    this->setWindowTitle("Send command");

    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(100, 20, 91, 24));
    btSend = new QPushButton(centralWidget);
    btSend->setObjectName(QString::fromUtf8("btSend"));
    btSend->setGeometry(QRect(5, 20, 91, 24));
    lbCommand = new QLabel(centralWidget);
    lbCommand->setObjectName(QString::fromUtf8("lbCommand"));
    lbCommand->setGeometry(QRect(5, 0, 71, 16));
    tlCommand = new QLineEdit(centralWidget);
    tlCommand->setObjectName(QString::fromUtf8("tlCommand"));
    tlCommand->setGeometry(QRect(90, 0, 180, 20));

    btCancel->setText("Cancel");
    btSend->setText("Send");
    lbCommand->setText("Command:");
    tlCommand->setText("GeneratingRandomDataImage");
}

//Constructor of TangoProperties
TangoProperties::TangoProperties(MainWindow *main){
    TangoProperties *MainWind = this;
    parent = main;
    centralWidget = new QWidget(MainWind);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setFixedSize(660, 50);
    this->move(100,100);

    /*init buttons*/
    btCancel = new QPushButton(centralWidget);
    btCancel->setObjectName(QString::fromUtf8("btCancel"));
    btCancel->setGeometry(QRect(560, 20, 91, 24));

    btNewDev = new QPushButton(centralWidget);
    btNewDev->setObjectName(QString::fromUtf8("btNewDev"));
    btNewDev->setGeometry(QRect(460, 20, 91, 24));

    btChangeDevice = new QPushButton(centralWidget);
    btChangeDevice->setObjectName(QString::fromUtf8("btChangeDevice"));
    btChangeDevice->setGeometry(QRect(360, 20, 91, 24));

    /*init labels and text lines*/
    tlServer = new QLineEdit(centralWidget);
    tlServer->setObjectName(QString::fromUtf8("tlServer"));
    tlServer->setGeometry(QRect(80, 0, 171, 20));
    lbServer = new QLabel(centralWidget);
    lbServer->setObjectName(QString::fromUtf8("lbServer"));
    lbServer->setGeometry(QRect(5, 0, 71, 16));

    tlDevice = new QLineEdit(centralWidget);
    tlDevice->setObjectName(QString::fromUtf8("tlDevice"));
    tlDevice->setGeometry(QRect(340, 0, 113, 20));
    lbDevice = new QLabel(centralWidget);
    lbDevice->setObjectName(QString::fromUtf8("lbDevice"));
    lbDevice->setGeometry(QRect(260, 0, 72, 16));

    lbAttr = new QLabel(centralWidget);
    lbAttr->setObjectName(QString::fromUtf8("lbAttr"));
    lbAttr->setGeometry(QRect(460, 0, 71, 16));
    tlAttr = new QLineEdit(centralWidget);
    tlAttr->setObjectName(QString::fromUtf8("tlAttr"));
    tlAttr->setGeometry(QRect(520, 0, 113, 20));

    /*init start text*/
    tlServer->setText("anka-tango3.ka.fzk.de:10000");
    lbServer->setText("Server name");
    lbAttr->setText("Attribute");
    tlAttr->setText("testImage");
    lbDevice->setText("Device name");
    tlDevice->setText("sys/tg_test/mytest");
    btNewDev->setText("Start new Dev");
    btChangeDevice->setText("Set Dev");
    btCancel->setText("Cancel");
}

//Creating Menu
void MainWindow::createMenu(){
    server = menuBar()->addMenu(QString("&Server"));
    server->addAction(addNewDevice);
    server->addAction(setDevice);
    server->addAction(pushCommand);
    server->addSeparator();
    server->addAction(exitAct);
    snapshot = menuBar()->addMenu(tr("&Snapshot"));
    snapshot->addAction(makeSnapshot);
    snapshot->addAction(saveSnapshot);

    snapshot->setEnabled(false);
    saveSnapshot->setEnabled(false);
    pushCommand->setEnabled(false);
}

//Init Actions
void MainWindow::createActions(){
    fprintf(stderr, "!!\n");
    makeSnapshot = new QAction(tr("&Make a snapshot"), this);
    makeSnapshot->setStatusTip(tr("Create a snapshot"));

    pushCommand = new QAction(tr("&Send a command"), this);
    pushCommand->setStatusTip(tr("Send a command"));
    connect(pushCommand, SIGNAL(triggered()), this, SLOT(setTangoCommand()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Finish working"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    addNewDevice = new QAction(tr("&Start new device"), this);
    addNewDevice->setStatusTip(tr("Start new device"));
    connect(addNewDevice, SIGNAL(triggered()), this, SLOT(setTangoDevice()));

    setDevice = new QAction(tr("&Set device"), this);
    setDevice->setStatusTip(tr("Set device"));
    connect(setDevice, SIGNAL(triggered()), this, SLOT(setTangoDevice()));

    saveSnapshot = new QAction(tr("&Save a snapshot"), this);
    saveSnapshot->setStatusTip(tr("Save a snapshot"));
}


void MainWindow::sendTangoCommand(){
    try{
    subWin[curDev].device->command_inout(cmdTangoLine->tlCommand->text().toAscii().constData());
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
    cmdTangoLine->close();
}

//Readin and displaying realtime data from the Tango server
//#threadArg - struct thread_data object, through it is send Mainwindon object (and more over in next version)
void MainWindow::startTesting(void* threadArg){    ///need in remaning!!!!!!
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadArg;
    MainWindow *parent;
    parent = my_data->parent;
    int iter = 0;                       //current iteration of reading data from Tango Server //not used
    QTime time;
    QTime timeReadData;
    //vector <unsigned char> val;
    QPalette pal;
    srand(3);
    time.start();
    fprintf(stderr, "==Starting Test%d==\n", my_data->threadNum);
    Tango::DeviceAttribute attr;
    int local = my_data->threadNum;

    ////seting size of realtime display widget//////////
    try{
    attr = parent->subWin[local].device->read_attribute(parent->subWin[local].attrName.toAscii()); //numOfWin
    }
    catch(Tango::ConnectionFailed){
          fprintf(stderr, "ConnectionFailed while reading attribute\n");
          exit(1);
    }
    catch(Tango::WrongData){
          fprintf(stderr, "Wrong Data while reading attribute\n");
          exit(1);
    }
    fprintf(stderr,"--Time of--- readingData=%d\n", timeReadData.restart());
    try{
        attr>>parent->subWin[local].val;
        parent->subWin[local].dimX = attr.get_dim_x();
        parent->subWin[local].dimY = attr.get_dim_y();
        subWin[countDev].resize(parent->subWin[local].dimX/4, parent->subWin[local].dimY);
    }
    catch(Tango::DevFailed){
         fprintf(stderr, "Dev Failed while reading attribute\n");
         exit(1);
    }
    //////////////////////////////////////////////////////

    while(parent->subWin[local].work){
        timeReadData.start();
        try{
        attr = parent->subWin[local].device->read_attribute(parent->subWin[local].attrName.toAscii()); //numOfWin
        }
        catch(Tango::ConnectionFailed){
              fprintf(stderr, "ConnectionFailed while reading attribute\n");
              exit(1);
              break;
        }
        catch(Tango::WrongData){
              fprintf(stderr, "Wrong Data while reading attribute\n");
              exit(1);
              break;
        }
        fprintf(stderr,"--Time of--- readingData=%d\n", timeReadData.restart());
        try{
            attr>>parent->subWin[local].val;
            if (parent->subWin[local].scale == 1.0){       //need in scaling???
                *parent->subWin[local].img = QImage(&parent->subWin[local].val[0],
                                                    attr.get_dim_x()/4,
                                                    attr.get_dim_y(),
                                                    attr.get_dim_x(),
                                                    QImage::Format_RGB32);
                parent->subWin[local].wgt->resize(attr.get_dim_x()/4, attr.get_dim_y());
            }
            else{
                *parent->subWin[local].img = parent->scaleImage(QImage(&parent->subWin[local].val[0],
                                                                    attr.get_dim_x()/4,
                                                                    attr.get_dim_y(),
                                                                    attr.get_dim_x(),
                                                                   QImage::Format_RGB32));
                parent->subWin[local].wgt->resize((attr.get_dim_x()/4) * parent->subWin[local].scale,
                                                  attr.get_dim_y() * parent->subWin[local].scale);
            }
            pal.setBrush(parent->subWin[local].wgt->backgroundRole(), QBrush(*parent->subWin[local].img));
            parent->subWin[local].wgt->setPalette(pal);

            fprintf(stderr,"iter=%d   -----devNum=%d ----- wholeTime=%d\n",iter, local, time.restart());
            parent->subWin[local].repaint();
        }
        catch(Tango::DevFailed){
             fprintf(stderr, "Dev Failed while reading attribute\n");
             exit(1);
             break;
        }
        QCoreApplication::processEvents(QEventLoop::AllEvents);    //Do System process
    }
}

void MainWindow::setSnapshotScale(){
    //try{
    bool ok =true;
    fprintf(stderr, "Snapshot scaling\n");
        subWinSnapPointer->scale = ui->tlScaleSnapshot->text().toDouble(&ok)/100.0; //Ok??????
        scaleImage();
        subWinSnapPointer->setWindowTitle(subWinSnapPointer->windowTitle().split("scale").first() + QString("scale ") + ui->tlScaleSnapshot->text());//QString().setNum(subWinSnapPointer->scale * 100);
    //}
    ///catch(){

    //}
}

void MainWindow::setRealtimeScale(){
    subWin[countDev].scale = ui->tlScaleRealTime->text().toDouble()/100.0;
    subWin[countDev].setWindowTitle( subWin[countDev].windowTitle().split("scale").first() + QString("scale ") + ui->tlScaleRealTime->text());//QString().setNum(subWin[countDev].scale * 100);
}


//Scale realtime data
//#image - realtime subwin image for scaling
QImage MainWindow::scaleImage(QImage image){
    return image.scaled(image.width()*subWin[curDev].scale, image.height()*subWin[curDev].scale);
}

//Scale snapshot
void MainWindow::scaleImage(){
    QPalette pal;
    subWinSnapPointer->wgt->hide();
    QImage tempImg; //*subWinSnapPointer->img
    tempImg = subWinSnapPointer->img->scaled(subWinSnapPointer->img->width() * subWinSnapPointer->scale, subWinSnapPointer->img->height()* subWinSnapPointer->scale);
    pal.setBrush(subWinSnapPointer->wgt->backgroundRole(), QBrush(tempImg));
    subWinSnapPointer->wgt->setPalette(pal);
    subWinSnapPointer->wgt->resize(tempImg.width()* subWinSnapPointer->scale, tempImg.height()* subWinSnapPointer->scale);
    subWinSnapPointer->wgt->show();
    fprintf(stderr,"---------------------Scaling-----------%d-----------------\n", subWinSnapPointer->numOfWin);
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
                    break;
                }
            }
        }
    }
    if(newState == Qt::WindowMinimized){
        fprintf(stderr,"Subwindow is minimaized\n");
        this->resize(50, 15);
    }
}

//set tango device
void MainWindow::addDevice(QString s){
        fprintf(stderr,"Set Tango device %s\n", s.toAscii().constData());
    try{
        *subWin[countDev].device = Tango::DeviceProxy(s.toAscii().constData());
    }
    catch(Tango::WrongNameSyntax e){
        fprintf(stderr,"Wrong Name Syntax of Tango Server\n");
        exit(1);
    }
    catch(Tango::ConnectionFailed e){
        fprintf(stderr,"Connection Failed with Tango Server\n");
        exit(1);
    }
    catch(Tango::DevFailed e){
            fprintf(stderr,"Is Failed Connection with Tango Server \n Check the name of TangoServer \n");
            exit(1);
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

//make a snapshot
void MainWindow::mkSnapshot(){
    ui->btScale->setEnabled(true);
    ui->btWriteImg->setEnabled(true);
    saveSnapshot->setEnabled(true);
    ui->btScaleSnapshot->setEnabled(true);

    QPalette pal;
    vector <unsigned char> val(subWin[curDev].val.size()); //image data
    SubWindow *tempSubWinSnapPointer = new SubWindow();
    QObject::connect(saveSnapshot, SIGNAL(triggered()), tempSubWinSnapPointer, SLOT(saveImg()));
    tempSubWinSnapPointer->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(tempSubWinSnapPointer,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
                     tempSubWinSnapPointer,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
    tempSubWinSnapPointer->setParent(this);
    tempSubWinSnapPointer->wgt->setParent(this);
    *tempSubWinSnapPointer->device = *subWin[curDev].device;
    tempSubWinSnapPointer->isSnapshot = true;
    tempSubWinSnapPointer->scale = subWin[curDev].scale;
    *tempSubWinSnapPointer->img = *subWin[curDev].img;
    tempSubWinSnapPointer->scrollArea->setWidget(tempSubWinSnapPointer->wgt);
    tempSubWinSnapPointer->numOfWin = 1+countImg;
    pal.setBrush(tempSubWinSnapPointer->wgt->backgroundRole(), QBrush( *tempSubWinSnapPointer->img));
    tempSubWinSnapPointer->wgt->setPalette(pal);
    tempSubWinSnapPointer->wgt->resize(subWin[curDev].dimX/4, subWin[curDev].dimY);

    tempSubWinSnapPointer->scrollArea->move(100,100);
    tempSubWinSnapPointer->scrollArea->resize(100, 100);
    tempSubWinSnapPointer->scrollArea->show();
    tempSubWinSnapPointer->setWidget(tempSubWinSnapPointer->scrollArea);
    tempSubWinSnapPointer->setWindowTitle((QString)"Snapshot of " + subWin[curDev].windowTitle() +
                                          (QString)" at " + QTime().currentTime().toString() +
                                          QString(" scale ") + QString().setNum(100));
    tempSubWinSnapPointer->setAttribute(Qt::WA_OpaquePaintEvent);
    fprintf(stderr,"!!SNAPSHOT!!\n");

    listSnap<<tempSubWinSnapPointer;            //add subwin to list
    area->hide();
    area->addSubWindow(tempSubWinSnapPointer);
    area->show();

    QObject::connect(ui->btWriteImg,SIGNAL(clicked()), tempSubWinSnapPointer,SLOT(saveImg()));
    val.erase(val.begin(), val.end());
    countImg++;
}

//save current snapshot
void SubWindow::saveImg(){
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(
              this,
              tr("Save Snapshot"),
              QDir::currentPath(),
                  tr("JPG (*.jpg);; TIFF (*.tiff);; BMP(*.bmp);; PNG(*.png);; JPEG(*jpeg);;"
                                "XBM(*.xbm);; XPM(*.xpm);; PPM(*.ppm)"),
                 &selectedFilter);
    if(filename != ""){
        parent->subWinSnapPointer->img->save(QString("./") + filename.split("\/").last() +
                                          QString(".") + selectedFilter.split("(").takeFirst().toLower(),
                                          selectedFilter.split("(").takeFirst().toLower().toAscii().constData());
        fprintf(stderr, "Save an Image\n");
    }
    else
        fprintf(stderr, "Saving an Image is canceled\n");
}

//open new device
void MainWindow::openDevInNewProc(){
    QProcess::startDetached("./TestApp",
                            QStringList() << this->tangoDev->tlServer->text()
                                << this->tangoDev->tlDevice->text()
                                << this->tangoDev->tlAttr->text(), "./");
    tangoDev->close();
}
