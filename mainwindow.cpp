/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QPainter>

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

    ui->cmbBox->addItems(QStringList()
                         << "TIFF"
                         << "BMP"
                         << "PNG"
                         << "JPEG"
                         << "JPG"
                         << "XBM"
                         << "XPM"
                         << "PPM");

    subWin = new SubWindow();
    firstTime = true;
    ui->btScale->setEnabled(false);
    ui->btMkSnapshot->setEnabled(false);
    ui->btWriteImg->setEnabled(false);

    QObject::connect(subWin,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
                     subWin,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}

//Destructor of mainwindow
MainWindow::~MainWindow()
{
    delete subWin;
    delete area;
    delete ui;
}

void MainWindow::createMenu(){
   // server = new QMenu();
   // snapshot = new QMenu();

    //server->addMenu(QString("&Server"));
//    server->addAction(setDevice);
    //server->addSeparator();
   // server->addAction(exitAct);
    snapshot = menuBar()->addMenu(tr("&Snapshot"));
    snapshot->addAction(makeSnapshot);
//    server->addSeparator();

//    ui->menuBar->addMenu(server);
//    ui->menuBar->addMenu(snapshot);
}

void MainWindow::createActions(){
    makeSnapshot = new QAction(tr("&makeSnapshot"), this);
    makeSnapshot->setShortcuts(QKeySequence::New);
    makeSnapshot->setStatusTip(tr("Create a snapshot"));
    connect(makeSnapshot, SIGNAL(triggered()), this, SLOT(mkSnapshot()));
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(makeSnapshot);
//    menu.addAction(copyAct);
//    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
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

//Readin and displaying realtime data from the Tango server
//#threadArg - struct thread_data object, through it is send Mainwindon object (and more over in next version)
void MainWindow::startTesting(void* threadArg){
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
    ///Tango::DeviceAttribute attr;///  use vector for coping data in snapshot
    Tango::DeviceAttribute attr;
    int local = my_data->threadNum;
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
            //*parent->subWin[local].img = QImage(&parent->subWin[local].val[0], attr.get_dim_x()/4, attr.get_dim_y(), attr.get_dim_x(), QImage::Format_RGB32);
            *parent->subWin[local].img = parent->scaleImage(QImage(&parent->subWin[local].val[0],
                                                                    attr.get_dim_x()/4,
                                                                    attr.get_dim_y(),
                                                                    attr.get_dim_x(),
                                                                   QImage::Format_RGB32));
            parent->subWin[local].dimX = attr.get_dim_x();
            parent->subWin[local].dimY = attr.get_dim_y();

            pal.setBrush(parent->subWin[local].wgt->backgroundRole(), QBrush(*parent->subWin[local].img));
            parent->subWin[local].wgt->setPalette(pal);
            parent->subWin[local].wgt->resize(attr.get_dim_x()/4, attr.get_dim_y());
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

//Scale realtime data
//#image - realtime subwin image for scaling
QImage MainWindow::scaleImage(QImage image){
    return image.scaled(image.width()+100, image.height()+100);
}

//Scale snapshot
void MainWindow::scaleImage(){
    QPalette pal;
    subWinSnapPointer->wgt->hide();
    *subWinSnapPointer->img = subWinSnapPointer->img->scaled(subWinSnapPointer->img->width()+100, subWinSnapPointer->img->height()+100);
    pal.setBrush(subWinSnapPointer->wgt->backgroundRole(), QBrush(*subWinSnapPointer->img));
    subWinSnapPointer->wgt->setPalette(pal);
    subWinSnapPointer->wgt->resize(subWinSnapPointer->wgt->width()+100, subWinSnapPointer->wgt->height()+100);
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

//Set parent widget for subwindow
void SubWindow::setParent(MainWindow *p){
    parent = p;
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

//start Tango device in real time
void MainWindow::changeDevice(){
    subWin[countDev].setParent(this);
    subWin[countDev].work = true;
    subWin[countDev].attrName = this->ui->tlAttr->text();
    QString s;
    s = (QString)"\/\/" + this->ui->tlServer->text() + (QString)"\/";
    s += this->ui->tlDevice->text();
    fprintf(stderr,"!_%s_!\n", s.toAscii().constData());
    addDevice(s);
    subWin[countDev].scrollArea->setWidget(subWin[countDev].wgt);
    fprintf(stderr,"!_111_!");
    subWin[countDev].scrollArea->move(100,100);
    subWin[countDev].scrollArea->resize(400, 300);
    subWin[countDev].scrollArea->show();
    subWin[countDev].resize(400, 300);
    subWin[countDev].numOfWin = countDev; /*need in Remaning*/
    subWin[countDev].isSnapshot = false;
    subWin[countDev].setWindowTitle((QString)"dev=" +
                                    QString(49+countDev) +
                                    (QString)" " +
                                    this->ui->tlServer->text());
    area->hide();
    if (firstTime){
        subWin[countDev].setWidget(subWin[countDev].scrollArea);
        area->addSubWindow(&subWin[countDev]);
    }

    subWin[countDev].scrollArea->move(0,30);
    subWin[countDev].scrollArea->resize(subWin[countDev].width()-2, subWin[countDev].height()-33);
    subWin[countDev].show();
    area->show();
    firstTime = false;
    thread_data data;
    data.parent = this;
    data.threadNum = subWin[countDev].numOfWin;
    fprintf(stderr, "\n=----%p----=%d\n", data.parent, subWin[countDev].numOfWin);
    ui->lbCurWorkiningDev->setText(QString("Cur Dev: ") + s + QString(" ") + ui->tlAttr->text());
    ui->btChangeDevice->setEnabled(false);
    ui->btMkSnapshot->setEnabled(true);
    startTesting((void*) &data);
}

//on change size of main window
void MainWindow::resizeEvent( QResizeEvent *e ){
    area->resize(e->size());
}

//on mouse press event at picture widget
void ImageWidget::mousePressEvent ( QMouseEvent * e){
    fprintf(stderr, "ImageWidget::mousePressEvent\n");
}

////on mouse move event at picture widget
void ImageWidget::mouseMoveEvent ( QMouseEvent * e){
    mouseX = e->x();
    mouseY = e->y();

    repaint();

    fprintf(stderr, "ImageWidget::mouseMoveEvent\n");
}

// name
// usage
// parameters

//on paint event
void ImageWidget::paintEvent( QPaintEvent * e){
    QPainter p(this);
    p.setPen(QPen(Qt::yellow, 2));
    p.drawLine(0, mouseY, this->width(), mouseY);
    p.drawLine(mouseX, 0, mouseX, this->height());
    fprintf(stderr, "ImageWidget::paintEvent\n");
}

void SubWindow::closeEvent ( QCloseEvent * closeEvent ){
    fprintf(stderr, "Del subWin\n");
    if (!isSnapshot){
        work = false;  //stop reading tango device
        parent->ui->btChangeDevice->setEnabled(true);
        parent->ui->btMkSnapshot->setEnabled(false);
    }
    else{
        QList<SubWindow*>::iterator iter;
        for (iter = parent->listSnap.begin(); iter < parent->listSnap.end(); ++iter){

             if(this == *iter){
                parent->subWinSnapPointer = NULL;
                fprintf(stderr,"!Delete a Snapshot!\n");
                qDeleteAll(iter, iter);     ////current point??>>>>>
                parent->listSnap.erase(iter);
                parent->ui->btScale->setEnabled(false);
                parent->ui->btWriteImg->setEnabled(false);
                break;
            }
        }
    }
}



void MainWindow::mkSnapshot(){
    ui->btScale->setEnabled(true);
    ui->btWriteImg->setEnabled(true);
    QPalette pal;
    vector <unsigned char> val(subWin[curDev].val.size()); //image data
    SubWindow *tempSubWinSnapPointer = new SubWindow();
    tempSubWinSnapPointer->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(tempSubWinSnapPointer,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
                     tempSubWinSnapPointer,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
    tempSubWinSnapPointer->setParent(this);
    *tempSubWinSnapPointer->device = *subWin[curDev].device;
    tempSubWinSnapPointer->isSnapshot = true;
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
    tempSubWinSnapPointer->setWindowTitle((QString)"Snapshot of " + subWin[curDev].windowTitle());
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

void SubWindow::saveImg(){

    if (parent->subWinSnapPointer && parent->ui->tlSaveImg->text() != ""){
      fprintf(stderr, "Save an Image\n");
      parent->subWinSnapPointer->img->save(parent->ui->tlSaveImg->text() + QString(".") + parent->ui->cmbBox->currentText().toLower().toAscii().constData(), parent->ui->cmbBox->currentText().toAscii().constData());
    //do some exception when file is opened at another app
    }
    else{
        fprintf(stderr, "Write the name of file for saving an Image\n");
        exit(1);
    }
}

void MainWindow::openDevInNewProc(){
    QProcess::startDetached("./TestApp",
                            QStringList() << this->ui->tlServer->text()
                                << this->ui->tlDevice->text()
                                << this->ui->tlAttr->text(), "./");
}

void MainWindow::closeEvent ( QCloseEvent * closeEvent){
    if  (subWin[0].isActiveWindow())
      subWin[0].close();
}
