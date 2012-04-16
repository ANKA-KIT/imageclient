#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    subWin = new SubWindow();

    subWinSnapPointer = new SubWindow();
    QObject::connect(subWin,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),subWin,
    SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete area;
    delete subWin;

    delete subWinSnapPointer;


}

SubWindow::~SubWindow(){
    delete parent;

    delete scrollArea;
    delete attr;
    delete device;
    delete wgt;

    delete img;
    //delete snapshot;
}

void MainWindow::insertSnapShot(){
//    SubWindow *pointer = new SubWindow();
//    pointer->nextSubWin = NULL;
//    subWinSnapTail->nextSubWin = pointer;
//    subWinSnapPointer = pointer;


   // subWinSnapTail = pointer;

  //  while (pointer != subWinSnapTail){
  //      pointer = pointer->nextSubWin;
  //  }

}

SubWindow::SubWindow(QWidget *parent, Qt::WindowFlags flags)
{
    attr = new Tango::DeviceAttribute();
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

    QObject::connect(this,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),this,
    SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}



//void MainWindow::startTesting(void* threadArg){}

//void st(void* threadArg){//SubWindow::
   // void* mythread::startTesting(void* threadArg){

//void* MainWindow::startTesting(void* threadArg){}

void MainWindow::startTesting(void* threadArg){
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadArg;
    MainWindow *parent;
    parent = my_data->parent;
    int iter = 0;
    int count = 200;
    QTime time;
    QTime timeReadData;
    vector <unsigned char> val;
    QPalette pal;
    //int *midle = new int[count];
    //int midVal = 0;
    srand(3);
   // QImage tempImg;
    time.start();
    fprintf(stderr, "==Starting Test%d==\n", my_data->threadNum);
    int local = my_data->threadNum;
    while(parent->subWin[local].work){
        timeReadData.start();
        fprintf(stderr, "\n==%d=----%p----=\n", local, parent);
        *parent->subWin[local].attr = parent->subWin[local].device->read_attribute(parent->subWin[local].attrName.toAscii()); //numOfWin
        fprintf(stderr,"----- readingData=%d\n", timeReadData.restart());
        *parent->subWin[local].attr>>val;
        *parent->subWin[local].img = parent->scaleImage(QImage(&val[0], parent->subWin[local].attr->get_dim_x()/4, parent->subWin[local].attr->get_dim_y(), parent->subWin[local].attr->get_dim_x(), QImage::Format_RGB32));
        //*parent->subWin[local].img = QImage(&val[0], parent->subWin[local].attr->get_dim_x()/4, parent->subWin[local].attr->get_dim_y(), parent->subWin[local].attr->get_dim_x(), QImage::Format_RGB32);
        pal.setBrush(parent->subWin[local].wgt->backgroundRole(), QBrush(*parent->subWin[local].img));
        parent->subWin[local].wgt->setPalette(pal);
        parent->subWin[local].wgt->resize(parent->subWin[local].attr->get_dim_x()/4, parent->subWin[local].attr->get_dim_y());
        fprintf(stderr,"iter=%d   -----devNum=%d ----- wholeTime=%d\n",iter, local, time.restart());
        //parent->subWin[local].scrollArea->repaint();  //this
        parent->subWin[local].repaint();
   //     midVal += midle[iter];
        iter++;
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
   // fprintf(stderr,"Midle time is %f\n",(float)midVal/(float)count);
}

QImage MainWindow::scaleImage(QImage image){
    return image.scaled(image.width()+100, image.height()+100);
}

void MainWindow::scaleImage(){
    QPalette pal;
    *subWinSnapPointer->img = subWinSnapPointer->img->scaled(subWinSnapPointer->img->width()+100, subWinSnapPointer->img->height()+100);
    //img->scaledToHeight(img->width()+100, Qt::FastTransformation);
    pal.setBrush(subWinSnapPointer->wgt->backgroundRole(), QBrush(*subWinSnapPointer->img));
    subWinSnapPointer->wgt->resize(subWinSnapPointer->wgt->width()+100, subWinSnapPointer->wgt->height()+100);
    subWinSnapPointer->wgt->setPalette(pal);
}

void SubWindow::focusInEvent ( QFocusEvent * e){
    /*if (&parent->subWin[0] == this){
        fprintf(stderr,"00000000");
    }
    else
        fprintf(stderr,"1111111");
        */
}

void SubWindow::handleWindowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState){

    fprintf(stderr,"uu00000000uu");
    if(newState == Qt::WindowActive){
        int i;
        int wins = parent->countDev+1;
        int winsSnap = parent->countImg+1;
        bool found = false;
        fprintf(stderr,"1111!!!!!!111");
        for (i = 0; i<wins; i++){

            if (this == &parent->subWin[i]){
                    parent->curDev = i;
                    parent->ui->lbCurWin->setText(QString("CurWin_") + QString(i+49));
                    found = true;
                    break;
            }
        }

        if (!found){
            //SubWindow *pointer = parent->subWinSnap;
            for (i = 0; i<parent->listSnap.size(); i++){
                 if(this == parent->listSnap.at(i)){
                    parent->curImg = i;
                    parent->ui->lbCurWin->setText(QString("CurSnap_") + QString(i+49));
                    parent->subWinSnapPointer = this;//pointer;
                    break;
                }
                 //pointer = pointer->nextSubWin;
            }

        }
    }
    if(newState == Qt::WindowMinimized){
        fprintf(stderr,"-----------------------------------");   ////////////
        this->resize(50, 15);
    }
}


void SubWindow::setParent(MainWindow *p){
    parent = p;
}


void MainWindow::addDevice(QString s){
/*        Tango::DeviceProxy *temp = new Tango::DeviceProxy[countDev]();
        //QScrollArea *tempScroll = new QScrollArea[countDev]();
        int i;
        for (i = 0; i<countDev; i++){
            *(temp + i) = *(device+i);
          //  *(tempScroll + i) = *(scrollArea + i);
        }
        fprintf(stderr,"!!!!+++%d", countDev);
        delete device;
        //delete scrollArea;
        fprintf(stderr,"del Device");
        device = new Tango::DeviceProxy[countDev+1]();
        scrollArea = new QScrollArea[countDev+1]();
        fprintf(stderr,"New device");




        for (i =0; i<countDev; i++){
            *(device+i) = *(temp + i);
            //*(scrollArea + i) = *(tempScroll + i);
        }
        */
        fprintf(stderr,"!!!!+++%s", s.toAscii().constData());

    try{
            *subWin[countDev].device = Tango::DeviceProxy(s.toAscii().constData());
            fprintf(stderr,"!!%d\n", countDev);
    }
    catch(Tango::WrongNameSyntax e){
        fprintf(stderr,"Wrong Name Syntax");
    }
    catch(Tango::ConnectionFailed e){
        fprintf(stderr,"Connection Failed");
    }

}

void MainWindow::addNewSubWin(){
/*    SubWindow *tempWin = new SubWindow[countDev](); //QMdiSubWindow[countDev]();
     int i;
    for (i=0; i<countDev; i++){
        tempWin[i] = subWin[i];
    }
    delete[] subWin;
    subWin = new SubWindow[countDev+1]();//SubWindow[countDev+1]();
    for (i =0; i<countDev; i++){
        *(subWin+i) = *(tempWin + i);
    }
*/
    //(subWin +countDev) = SubWindowd();
    //SubWindow tempWin;// = SubWindow[countDev]();
}

void MainWindow::delSubWin(){

}

void MainWindow::test(){}
void testw(int i){}

void MainWindow::changeDevice(){
    subWin[countDev].setParent(this);
    subWin[countDev].work = true;
    subWin[countDev].attrName = this->ui->tlAttr->text();
    QString s;
    s = (QString)"\/\/" + this->ui->tlServer->text() + (QString)"\/";
    s += this->ui->tlDevice->text();
    fprintf(stderr,"!__!");
    addDevice(s);
//    addNewSubWin();
    subWin[countDev].scrollArea->setWidget(subWin[countDev].wgt);
    fprintf(stderr,"!_111_!");
    subWin[countDev].scrollArea->move(100,100);
    subWin[countDev].scrollArea->resize(400, 300);
    subWin[countDev].scrollArea->show();
    subWin[countDev].resize(400, 300);
    subWin[countDev].numOfWin = countDev; /*need in Remaning*/
    subWin[countDev].isSnapshot = false;
    subWin[countDev].setWidget(subWin[countDev].scrollArea);
    fprintf(stderr,"!_4333334_!");
    subWin[countDev].setWindowTitle((QString)"dev=" + QString(49+countDev) + (QString)" " + this->ui->tlServer->text());//QString::fromStdString(device[countDev].name()));
    fprintf(stderr,"!!!!");
///////    subWin[countDev].setAttribute(Qt::WA_DeleteOnClose);///////////////
    area->hide();
    area->addSubWindow(&subWin[countDev]);

    subWin[countDev].scrollArea->move(0,30);
    subWin[countDev].scrollArea->resize(subWin[countDev].width()-2, subWin[countDev].height()-33);
    subWin[countDev].show();
//    subWin[countDev].activateWindow();
  //  subWin[countDev].resize(subWin[countDev].width(), subWin[countDev].height());
    area->show();
    fprintf(stderr,"!_44444444_!");

    thread_data data;
    data.parent = this;
    data.threadNum = subWin[countDev].numOfWin;
    fprintf(stderr, "\n=----%p----=%d\n", data.parent, subWin[countDev].numOfWin);
  //  countDev++;   //if not 1 dev per 1 window
    ui->lbCurWorkiningDev->setText(QString("Cur Dev: ") + s + QString(" ") + ui->tlAttr->text());
    startTesting((void*) &data);
}


void MainWindow::resizeEvent( QResizeEvent *e ){
    area->resize(e->size());
}

void MainWindow::mousePressEvent ( QMouseEvent * e){
    fprintf(stderr, "rerwer");
}

void ImageWidget::mousePressEvent ( QMouseEvent * e){
    fprintf(stderr, "wwwww");
}
void ImageWidget::mouseMoveEvent ( QMouseEvent * e){
    mouseX = e->x();
    mouseY = e->y();

    repaint();

    fprintf(stderr, "moooooo");
}

void ImageWidget::paintEvent( QPaintEvent * e){
    QPainter p(this);
    p.setPen(QPen(Qt::yellow, 2));
    p.drawLine(0, mouseY, this->width(), mouseY);
    p.drawLine(mouseX, 0, mouseX, this->height());
    fprintf(stderr, "aaaaaaaaa___");
}

void SubWindow::closeEvent ( QCloseEvent * closeEvent ){
    fprintf(stderr, "Del subWin");
    if (!isSnapshot)
        work = false;  //stop reading tango device
}

/*void SubWindow::delSubWin(QCloseEvent * closeEvent ){
        fprintf(stderr, "Del subWin");
}
*/

mythread::mythread() : QThread()
{
    moveToThread(this); //initiates thread
}

mythread::mythread(MainWindow *w, int n) : QThread(){
    moveToThread(this);
    data.parent = w;
    data.threadNum = n;
}

void mythread::doTheWork(){emit signal((void*) &data);}
void mythread::stop(){}
void mythread::run(){
    //startTesting(&data);
    fprintf(stderr, "tread runing___%d", data.threadNum);
    int i=0;
  // exec();
    QTimer timer;
         connect(&timer, SIGNAL(timeout()), this, SLOT(doTheWork()), Qt::DirectConnection);
         timer.setInterval(100);  //100
         timer.start();   // puts one event in the threads event queue
         exec();
    timer.stop();

//    while (i<200)
  //  {emit signal((void*) &data);
//        i++;
//    }

}

void MainWindow::mkSnapshot(){
    //insertSnapShot();
    QPalette pal;
    vector <unsigned char> val;
 /*   subWinSnap[countImg].setParent(this);
    *subWinSnap[countImg].device = *subWin[curDev].device;
    subWinSnap[countImg].isSnapshot = true;
    *subWinSnap[countImg].img = *subWin[curDev].img;
    subWinSnap[countImg].scrollArea->setWidget(subWinSnap[countImg].wgt);
    *subWinSnap[countImg].attr = *subWin[curDev].attr;
    subWinSnap[countImg].numOfWin = 1+countImg;
    *subWinSnap[countImg].attr>>val;
    *subWinSnap[countImg].img = QImage(&val[0], subWinSnap[countImg].attr->get_dim_x()/4, subWinSnap[countImg].attr->get_dim_y(), subWinSnap[countImg].attr->get_dim_x(), QImage::Format_RGB32);
    pal.setBrush(subWinSnap[countImg].wgt->backgroundRole(), QBrush( *subWinSnap[countImg].img));
    subWinSnap[countImg].wgt->setPalette(pal);
    subWinSnap[countImg].wgt->resize(subWinSnap[countImg].attr->get_dim_x()/4, subWinSnap[countImg].attr->get_dim_y());

    subWinSnap[countImg].scrollArea->move(100,100);
    subWinSnap[countImg].scrollArea->resize(100, 100);
    subWinSnap[countImg].scrollArea->show();
    subWinSnap[countImg].numOfWin = countImg;
    subWinSnap[countImg].setWidget(subWinSnap[countImg].scrollArea);
    subWinSnap[countImg].setWindowTitle((QString)"Snapshot of " + subWin[curDev].windowTitle());
    */
    subWinSnapPointer = new SubWindow();
    QObject::connect(subWinSnapPointer,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),subWinSnapPointer,
    SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
    subWinSnapPointer->setParent(this);
    *subWinSnapPointer->device = *subWin[curDev].device;
      subWinSnapPointer->isSnapshot = true;
        *subWinSnapPointer->img = *subWin[curDev].img;
        subWinSnapPointer->scrollArea->setWidget(subWinSnapPointer->wgt);
        *subWinSnapPointer->attr = *subWin[curDev].attr;
        subWinSnapPointer->numOfWin = 1+countImg;
        *subWinSnapPointer->attr>>val;
        *subWinSnapPointer->img = QImage(&val[0], subWinSnapPointer->attr->get_dim_x()/4, subWinSnapPointer->attr->get_dim_y(), subWinSnapPointer->attr->get_dim_x(), QImage::Format_RGB32);
        pal.setBrush(subWinSnapPointer->wgt->backgroundRole(), QBrush( *subWinSnapPointer->img));
        subWinSnapPointer->wgt->setPalette(pal);
        subWinSnapPointer->wgt->resize(subWinSnapPointer->attr->get_dim_x()/4, subWinSnapPointer->attr->get_dim_y());

        subWinSnapPointer->scrollArea->move(100,100);
        subWinSnapPointer->scrollArea->resize(100, 100);
        subWinSnapPointer->scrollArea->show();
        subWinSnapPointer->numOfWin = countImg;
        subWinSnapPointer->setWidget(subWinSnapPointer->scrollArea);
        subWinSnapPointer->setWindowTitle((QString)"Snapshot of " + subWin[curDev].windowTitle());
    fprintf(stderr,"!!SNAPSHOT!!");
    area->hide();
    area->addSubWindow(subWinSnapPointer);
    area->show();
   // subWinSnapTail = subWinSnapPointer;
    listSnap<<subWinSnapPointer;
    countImg++;
}


void MainWindow::openDevInNewProc(){
    QString s;
    s = this->ui->tlServer->text() + (QString)" ";
    s += this->ui->tlDevice->text() + (QString)" " + this->ui->tlAttr->text() + (QString)" &";
    system(QString(QString("./TestApp ") + s).toAscii());
   // system("pwd");
}

void MainWindow::closeEvent ( QCloseEvent * closeEvent){
    emit subWin[0].closeEvent(closeEvent);
}
