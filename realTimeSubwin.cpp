/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

//Filling val
void setUCharVal(Tango::DeviceAttribute attr, vector <unsigned char>& val){
    try{
        attr>>val;
    }
    catch(Tango::DevFailed){
         fprintf(stderr, "Dev Failed while reading attribute\n");
         //ui->lbWork->setPalette(isWork(2));
         exit(1);
    }
}

//read bool value from tango devce
void setBoolVal(Tango::DeviceAttribute attr, bool& val){
    try{
        attr>>val;
        fprintf(stderr, "Bool Val = %d\n", val);
    }
    catch(Tango::DevFailed){
         fprintf(stderr, "Dev Failed while reading attribute\n");
         //ui->lbWork->setPalette(isWork(2));
         exit(1);
    }
}


//Set Tango attr
Tango::DeviceAttribute MainWindow::setTangoAttr(Tango::DeviceProxy &device, QString attrName){
    Tango::DeviceAttribute attr;
    try{
        attr = device.read_attribute(attrName.toAscii());
        return attr;
    }
    catch(Tango::ConnectionFailed){
          fprintf(stderr, "ConnectionFailed while reading attribute\n");
        //  ui->lbWork->setPalette(isWork(2));
          exit(1);
    }
    catch(Tango::WrongData){
          fprintf(stderr, "Wrong Data while reading attribute\n");
         // ui->lbWork->setPalette(isWork(2));
          exit(1);
    }

}

//set tango device
Tango::DeviceProxy MainWindow::addDevice(QString s){
    fprintf(stderr,"Set Tango device %s\n", s.toAscii().constData());
    try{
        Tango::DeviceProxy dev;
        dev = Tango::DeviceProxy(s.toAscii().constData());
        return dev;
    }
    catch(Tango::WrongNameSyntax e){
        fprintf(stderr,"Wrong Name Syntax of Tango Server\n");
     //   ui->lbWork->setPalette(QPalette( isWork(2)));
        ui->lbWork->setText("NOT WORK");
        ui->lbWork->setPalette(QPalette(Qt::darkRed));
        exit(1);
    }
    catch(Tango::ConnectionFailed e){
        fprintf(stderr,"Connection Failed with Tango Server\n");
        //ui->lbWork->setPalette(QPalette( isWork(2)));
        ui->lbWork->setText("NOT WORK");
        ui->lbWork->setPalette(QPalette(Qt::darkRed));
        exit(1);
    }
    catch(Tango::DevFailed e){
            fprintf(stderr,"Is Failed Connection with Tango Server \n Check the name of TangoServer \n");
            //ui->lbWork->setPalette(QPalette( isWork(2)));
            ui->lbWork->setText("NOT WORK");
            ui->lbWork->setPalette(QPalette(Qt::darkRed));
            exit(1);
    }
}

//set Realtime Scale value
void MainWindow::setRealtimeScale(){
    bool ok = true;
    double temp;
    temp = ui->tlScaleRealTime->text().toDouble(&ok);
    if (ok){
        subWin->scale = temp/100.0;
        subWin->setWindowTitle( subWin->windowTitle().split("scale").first() + QString("scale ") + ui->tlScaleRealTime->text());
    }
    else{
        fprintf(stderr, "Put correct number to the RealTime scale line");
        ui->lbWork->setText("NOT WORK");
        ui->lbWork->setPalette(QPalette(Qt::darkRed));
        //ui->lbWork->setPalette(QPalette( isWork(2)));
        exit(1);
    }
}

//Scale realtime data
//#image - realtime subwin image for scaling
QImage MainWindow::scaleImage(QImage image){
    return image.scaled(image.width()*subWin->scale, image.height()*subWin->scale);
}

void MainWindow::setImage(Tango::DeviceAttribute &attr){
    QPalette pal;
    if (subWin->scale == 1.0){       //need in scaling???
            *subWin->img = QImage(&subWin->val[0],
                                                attr.get_dim_x()/delim,
                                                attr.get_dim_y(),
                                                attr.get_dim_x(),
                                                (QImage::Format )intColorFormat);
            subWin->wgt->resize(attr.get_dim_x()/delim, attr.get_dim_y());
        }
    else{
            *subWin->img = scaleImage(QImage(&subWin->val[0],
                                                                attr.get_dim_x()/delim,
                                                                attr.get_dim_y(),
                                                                attr.get_dim_x(),
                                                                (QImage::Format)intColorFormat));
            subWin->wgt->resize((attr.get_dim_x()/delim) * subWin->scale,
                                              attr.get_dim_y() * subWin->scale);
    }
    pal.setBrush(subWin->wgt->backgroundRole(), QBrush(*subWin->img));
    subWin->wgt->setPalette(pal);
}


//Readin and displaying realtime data from the Tango server
void MainWindow::startTesting(){
    int iter = 0;                       //current iteration of reading data from Tango Server //not used
    QTime time;
    QTime timeReadData;
    time.start();
    fprintf(stderr, "==Starting Test==\n");
    Tango::DeviceAttribute attr;

    ////seting size of realtime display widget//////////
    attr = setTangoAttr(*subWin->device, subWin->attrName);
    fprintf(stderr,"--Time of--- readingData=%d\n", timeReadData.restart());

    setUCharVal(attr, subWin->val);

    subWin->dimX = attr.get_dim_x();
    subWin->dimY = attr.get_dim_y();
    subWin->resize(subWin->dimX/delim, subWin->dimY);
    //////////////////////////////////////////////////////

    while(subWin->work){
        ui->lbWork->setText("WORK");
        ui->lbWork->setPalette(QPalette(Qt::green));
        //ui->lbWork->setPalette(QPalette( isWork(0)));
        timeReadData.start();
        attr = setTangoAttr(*subWin->device, subWin->attrName);
        fprintf(stderr,"--Time of--- readingData=%d\n", timeReadData.restart());

        setUCharVal(attr, subWin->val);
        setImage(attr);
        fprintf(stderr,"x=%d y=%d\n",subWin->img->width(), subWin->img->height());
        fprintf(stderr,"iter=%d   ---- ----- wholeTime=%d\n",iter,  time.restart());
        subWin->repaint();
        QCoreApplication::processEvents(QEventLoop::AllEvents);    //Do System process
    }
    //ui->lbWork->setPalette(QPalette( isWork(1)));
    ui->lbWork->setText("NOT WORK");
    ui->lbWork->setPalette(QPalette(Qt::red));
}

//Init realtime reading data subwindow
void MainWindow::changeDevice(){
    subWin->setParent(this);
    subWin->wgt->setParent(this);

    snapshot->setEnabled(true);
    ui->btScaleRealTime->setEnabled(true);
    subWin->work = true;
    subWin->attrName = this->tangoDev->tlAttr->text();
    QString s;
    s =     (QString)"\/\/" + this->tangoDev->tlServer->text() +
            (QString)"\/" + tangoDev->tlDevice->text();
    fprintf(stderr,"!_%s_!\n", s.toAscii().constData());
    *subWin->device = addDevice(s);
    subWin->scrollArea->setWidget(subWin->wgt);
    subWin->scrollArea->move(100,100);
    subWin->scrollArea->resize(400, 300);
    subWin->scrollArea->show();
    subWin->resize(400, 300);
    subWin->numOfWin = 0;//countDev; /*need in Remaning*/
    subWin->isSnapshot = false;
    subWin->scale = ui->tlScaleRealTime->text().toDouble()/100;
    subWin->setWindowTitle(this->tangoDev->tlDevice->text() +
                                    QString(" scale ") + ui->tlScaleRealTime->text());
    area->hide();
    if (firstTime){
        QObject::connect(makeSnapshot, SIGNAL(triggered()), this, SLOT(mkSnapshot()));
        subWin->setWidget(subWin->scrollArea);
        area->addSubWindow(subWin);
    }
    subWin->scrollArea->resize(subWin->width()-2, subWin->height()-33);
    subWin->show();
    area->show();
    firstTime = false;
    ui->lbCurWorkiningDev->setText(QString("Cur Dev: ") + s + QString(" ") + tangoDev->tlAttr->text());

    ui->btChangeDevice->setEnabled(false);
    ui->btMkSnapshot->setEnabled(true);
    makeSnapshot->setEnabled(true);
    setDevice->setEnabled(false);
    pushCommand->setEnabled(true);

/*//Reading FLIP value
    bool flipHorizontal = true;
    bool flipVertical = true;
    setBoolVal(setTangoAttr(*subWin->device, (QString)"FlipHorizontal"), flipHorizontal);
    QVariant varValue(flipHorizontal);
    ui->lbFlipHorizontal->setText("FlipHorizontal " +  varValue.toString());//QString::number(flipHorizontal));
    setBoolVal(setTangoAttr(*subWin->device, (QString)"FlipVertical"), flipVertical);
    QVariant varValueV(flipVertical);
    ui->lbFlipVertical->setText("FlipVertical " + varValueV.toString());//QString::number(flipVertical));
*/

    tangoDev->close();
    delete tangoDev;
    tangoDev = NULL;
    startTesting();
}

