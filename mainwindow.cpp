#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const int Count = 10;

    subWin = new SubWindow[Count]();
    subWinSnap = new SubWindow[Count]();

    mutex = new pthread_mutex_t();
    sem_init(&threadCount, 0, 0);
//    thr = new pthread_t[4]();
    thr = new mythread[Count]();

    int i;
    for (i =0; i<Count; i++){
        QObject::connect(&subWin[i],SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),&subWin[i],
        SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
        QObject::connect(&subWinSnap[i],SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),&subWinSnap[i],
        SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
    }
    *mutex = PTHREAD_MUTEX_INITIALIZER;
}

MainWindow::~MainWindow()
{
    delete ui;

    delete area;
    delete subWin;

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
    time.start();
    fprintf(stderr, "==Starting Test%d==\n", my_data->threadNum);
    int local = my_data->threadNum;
    while(parent->subWin[local].work){
        timeReadData.start();
        fprintf(stderr, "\n==%d=----%p----=\n", local, parent);
        *parent->subWin[local].attr = parent->subWin[local].device->read_attribute(parent->subWin[local].attrName.toAscii()); //numOfWin
        fprintf(stderr,"----- readingData=%d\n", timeReadData.restart());
        *parent->subWin[local].attr>>val;
        *parent->subWin[local].img = QImage(&val[0], parent->subWin[local].attr->get_dim_x()/4, parent->subWin[local].attr->get_dim_y(), parent->subWin[local].attr->get_dim_x(), QImage::Format_RGB32);
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

void MainWindow::scaleImage(){
    QPalette pal;
    *subWinSnap[curImg].img = subWinSnap[curImg].img->scaled(subWinSnap[curImg].img->width()+100, subWinSnap[curImg].img->height()+100);
    //img->scaledToHeight(img->width()+100, Qt::FastTransformation);
    pal.setBrush(subWinSnap[curImg].wgt->backgroundRole(), QBrush(*subWinSnap[curImg].img));
    subWinSnap[curImg].wgt->resize(subWinSnap[curImg].wgt->width()+100, subWinSnap[curImg].wgt->height()+100);
    subWinSnap[curImg].wgt->setPalette(pal);
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
            for (i = 0; i<winsSnap; i++){
                if(this == &parent->subWinSnap[i]){
                    parent->curImg = i;
                    parent->ui->lbCurWin->setText(QString("CurSnap_") + QString(i+49));
                    break;
                }
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
    //fprintf(stderr,"!_22222_!");
/*//    QPalette pal;
//    vector <unsigned char> val;
 //   attr[countDev] = device[countDev].read_attribute("testImage");
 //   attr[countDev]>>val;
 //   img[countDev] = QImage(&val[0], attr[countDev].get_dim_x()/4, attr[countDev].get_dim_y(), attr[countDev].get_dim_x(), QImage::Format_RGB32);
 //   pal.setBrush(wgt[countDev].backgroundRole(), QBrush(img[countDev]));
 //   wgt[countDev].setPalette(pal);
 //   wgt[countDev].resize(attr[countDev].get_dim_x()/4, attr[countDev].get_dim_y());
 */
    subWin[countDev].scrollArea->move(100,100);
    subWin[countDev].scrollArea->resize(100, 100);
    subWin[countDev].scrollArea->show();
    subWin[countDev].numOfWin = countDev; /*need in Remaning*/
    subWin[countDev].isSnapshot = false;
    subWin[countDev].setWidget(subWin[countDev].scrollArea);
    fprintf(stderr,"!_4333334_!");
    subWin[countDev].setWindowTitle((QString)"dev=" + QString(49+countDev) + (QString)" " + this->ui->tlServer->text());//QString::fromStdString(device[countDev].name()));
    fprintf(stderr,"!!!!");
///////    subWin[countDev].setAttribute(Qt::WA_DeleteOnClose);///////////////
    area->hide();
    area->addSubWindow(&subWin[countDev]);//subWin[countDev].activateWindow();
    area->show();
    fprintf(stderr,"!_44444444_!");

//    pthread_mutex_lock(mutex);
  //  sem_post(&threadCount);
    thread_data data;
    data.parent = this;
  //  data.threadNum = new int;
    data.threadNum = subWin[countDev].numOfWin;
    countDev++;
 //   pthread_mutex_unlock(mutex);

 //   sem_wait(&threadCount);//&parent->threadCount);
    fprintf(stderr, "\n=----%p----=%d\n", data.parent, subWin[countDev-1].numOfWin);
  //  pthread_create(&thr[countDev-1], NULL, startTesting, (void*) &data);

    /*
    QObject::connect(&thr[countDev-1], SIGNAL(signal(void*)), this, SLOT(startTesting(void*)), Qt::QueuedConnection);
    thr[countDev-1].data = data;
    thr[countDev-1].start();
    */
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
    work = false;
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

    QPalette pal;
    vector <unsigned char> val;
    subWinSnap[countImg].setParent(this);
    *subWinSnap[countImg].device = *subWin[curDev].device;
    subWinSnap[countImg].isSnapshot = true;
    *subWinSnap[countImg].img = *subWin[curDev].img;
    subWinSnap[countImg].scrollArea->setWidget(subWinSnap[countImg].wgt);
    *subWinSnap[countImg].attr = *subWin[curDev].attr;
 /*     pal.setBrush(subWinSnap[countImg].wgt->backgroundRole(), QBrush( *subWinSnap[countImg].img));
    subWinSnap[countImg].wgt->setPalette(pal);
    subWinSnap[countImg].wgt->resize(subWinSnap[countImg].attr->get_dim_x()/4, subWinSnap[countImg].attr->get_dim_y());
*/
    *subWinSnap[countImg].attr>>val;
    *subWinSnap[countImg].img = QImage(&val[0], subWinSnap[countImg].attr->get_dim_x()/4, subWinSnap[countImg].attr->get_dim_y(), subWinSnap[countImg].attr->get_dim_x(), QImage::Format_RGB32);
    pal.setBrush(subWinSnap[countImg].wgt->backgroundRole(), QBrush( *subWinSnap[countImg].img));
    subWinSnap[countImg].wgt->setPalette(pal);
    subWinSnap[countImg].wgt->resize(subWinSnap[countImg].attr->get_dim_x()/4, subWinSnap[countImg].attr->get_dim_y());

    subWinSnap[countImg].scrollArea->move(100,100);
    subWinSnap[countImg].scrollArea->resize(100, 100);
    subWinSnap[countImg].scrollArea->show();
    subWinSnap[countImg].numOfWin = countImg; /*need in Remaning*/
    subWinSnap[countImg].setWidget(subWinSnap[countImg].scrollArea);
    subWinSnap[countImg].setWindowTitle((QString)"Snapshot of " + subWin[curDev].windowTitle());//QString::fromStdString(device[countDev].name()));
    fprintf(stderr,"!!SNAPSHOT!!");
    area->hide();
    area->addSubWindow(&subWinSnap[countImg]);
    area->show();
    countImg++;

}


void MainWindow::openDevInNewProc(){
    QString s;
    s = this->ui->tlServer->text() + (QString)" ";
    s += this->ui->tlDevice->text() + (QString)" " + this->ui->tlAttr->text() + (QString)" &";
    system(QString(QString("./TestApp ") + s).toAscii());
   // system("pwd");
}
