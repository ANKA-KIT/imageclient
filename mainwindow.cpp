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
    firstTime = true;
    ui->btScale->setEnabled(false);
    ui->btMkSnapshot->setEnabled(false);

    QObject::connect(subWin,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
                     subWin,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}

MainWindow::~MainWindow()
{
    delete subWin;

    delete area;
    delete ui;
}

SubWindow::~SubWindow(){
//    delete attr;
    delete device;
    delete img;
    delete wgt;
    delete scrollArea;
    fprintf(stderr,"\n!_Delete SubWin in   destructor_!");
}

void MainWindow::insertSnapShot(){

}

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

    QObject::connect(this,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),this,
    SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}

void MainWindow::startTesting(void* threadArg){
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadArg;
    MainWindow *parent;
    parent = my_data->parent;
    int iter = 0;
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
        fprintf(stderr, "\n==%d=----%p----=\n", local, parent);
        try{
        attr = parent->subWin[local].device->read_attribute(parent->subWin[local].attrName.toAscii()); //numOfWin
        }
        catch(Tango::ConnectionFailed){
              fprintf(stderr, "ConnectionFailed while reading attribute");
              break;
        }
        catch(Tango::WrongData){
              fprintf(stderr, "Wrong Data while reading attribute");
              break;
        }
        fprintf(stderr,"----- readingData=%d\n", timeReadData.restart());
        try{
            attr>>parent->subWin[local].val;
            *parent->subWin[local].img = parent->scaleImage(QImage(&parent->subWin[local].val[0],
                                                                    attr.get_dim_x()/4,
                                                                    attr.get_dim_y(),
                                                                    attr.get_dim_x(),
                                                                   QImage::Format_RGB32));
            parent->subWin[local].dimX = attr.get_dim_x();
            parent->subWin[local].dimY = attr.get_dim_y();
            //*parent->subWin[local].img = QImage(&val[0], parent->subWin[local].attr->get_dim_x()/4, parent->subWin[local].attr->get_dim_y(), parent->subWin[local].attr->get_dim_x(), QImage::Format_RGB32);
            pal.setBrush(parent->subWin[local].wgt->backgroundRole(), QBrush(*parent->subWin[local].img));
            parent->subWin[local].wgt->setPalette(pal);
            parent->subWin[local].wgt->resize(attr.get_dim_x()/4, attr.get_dim_y());
            fprintf(stderr,"iter=%d   -----devNum=%d ----- wholeTime=%d\n",iter, local, time.restart());
            parent->subWin[local].repaint();
        }
        catch(Tango::DevFailed){
             fprintf(stderr, "Dev Failed while reading attribute");
             break;
        }


//        iter++;
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
}

QImage MainWindow::scaleImage(QImage image){
    return image.scaled(image.width()+100, image.height()+100);
}

void MainWindow::scaleImage(){
    QPalette pal;
    *subWinSnapPointer->img = subWinSnapPointer->img->scaled(subWinSnapPointer->img->width()+100, subWinSnapPointer->img->height()+100);
    pal.setBrush(subWinSnapPointer->wgt->backgroundRole(), QBrush(*subWinSnapPointer->img));
    subWinSnapPointer->wgt->resize(subWinSnapPointer->wgt->width()+100, subWinSnapPointer->wgt->height()+100);
    subWinSnapPointer->wgt->setPalette(pal);
}

void SubWindow::focusInEvent ( QFocusEvent * e){

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
            for (i = 0; i<parent->listSnap.size(); i++){
                 if(this == parent->listSnap.at(i)){
                    parent->curImg = i;
                    parent->ui->lbCurWin->setText(QString("CurSnap_") + QString(i+49));
                    parent->subWinSnapPointer = this;
                    parent->ui->btScale->setEnabled(true);
                    fprintf(stderr,"77777777777777777777777777777777777777777777777777");
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
        fprintf(stderr,"!!!!+++%s", s.toAscii().constData());
    try{
            *subWin[countDev].device = Tango::DeviceProxy(s.toAscii().constData());
            fprintf(stderr,"!!%d\n", countDev);
    }
    catch(Tango::WrongNameSyntax e){
        fprintf(stderr,"Wrong Name Syntax of Tango Server");
        exit(1);
    }
    catch(Tango::ConnectionFailed e){
        fprintf(stderr,"Connection Failed with Tango Server");
        exit(1);
    }
    catch(Tango::DevFailed e){
            fprintf(stderr,"Is Failed Connection with Tango Server \n Check the name of TangoServer \n");
            exit(1);
    }

}

void MainWindow::addNewSubWin(){

}

void MainWindow::delSubWin(){

}

void MainWindow::test(){}

void MainWindow::changeDevice(){
    subWin[countDev].setParent(this);
    subWin[countDev].work = true;
    subWin[countDev].attrName = this->ui->tlAttr->text();
    QString s;
    s = (QString)"\/\/" + this->ui->tlServer->text() + (QString)"\/";
    s += this->ui->tlDevice->text();
    fprintf(stderr,"!_%s_!", s.toAscii().constData());
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
    if (!isSnapshot){
        work = false;  //stop reading tango device
        parent->ui->btChangeDevice->setEnabled(true);
        parent->ui->btMkSnapshot->setEnabled(false);
    }
    else{
        //int i;
        QList<SubWindow*>::iterator iter;
        for (iter = parent->listSnap.begin(); iter < parent->listSnap.end(); ++iter){

             if(this == *iter){
                parent->subWinSnapPointer = NULL;
                fprintf(stderr,"!_5555555555555555555555555555555555555555_!");
                qDeleteAll(iter, iter);     ////current point??>>>>>
                parent->listSnap.erase(iter);
                parent->ui->btScale->setEnabled(false);
                break;
            }
        }
    }
}



void MainWindow::mkSnapshot(){
    ui->btScale->setEnabled(true);
    QPalette pal;
    vector <unsigned char> val(subWin[curDev].val.size()); //= new vector<unsigned char>(subWin[curDev].val.size());
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
    copy(subWin[curDev].val.begin(), subWin[curDev].val.end(), val.begin());
    fprintf(stderr,"!!copy SNAPSHOT %d - %d!!", val.begin()[100], subWin[curDev].val[100]);
    /*  tempSubWinSnapPointer->attr = new Tango::DeviceAttribute(*subWin->attr);
        try{
        *tempSubWinSnapPointer->attr>>val;
        }
        catch(Tango::WrongData){
            fprintf(stderr,"MYEROR here------------");
        }
    */
    *tempSubWinSnapPointer->img = QImage(&val[0],  //&subWin[curDev].val[0],
                                         subWin[curDev].dimX/4,
                                         subWin[curDev].dimY,
                                         subWin[curDev].dimX,
                                         QImage::Format_RGB32);
    pal.setBrush(tempSubWinSnapPointer->wgt->backgroundRole(), QBrush( *tempSubWinSnapPointer->img));
    tempSubWinSnapPointer->wgt->setPalette(pal);
    tempSubWinSnapPointer->wgt->resize(subWin[curDev].dimX/4, subWin[curDev].dimY);

    tempSubWinSnapPointer->scrollArea->move(100,100);
    tempSubWinSnapPointer->scrollArea->resize(100, 100);
    tempSubWinSnapPointer->scrollArea->show();
    tempSubWinSnapPointer->numOfWin = countImg;
    tempSubWinSnapPointer->setWidget(tempSubWinSnapPointer->scrollArea);
    tempSubWinSnapPointer->setWindowTitle((QString)"Snapshot of " + subWin[curDev].windowTitle());
    fprintf(stderr,"!!SNAPSHOT!!");
    area->hide();
    listSnap<<tempSubWinSnapPointer;
    area->addSubWindow(tempSubWinSnapPointer);
    area->show();

    val.erase(val.begin(), val.end());
    countImg++;
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
