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
Tango::DeviceAttribute setTangoAttr(Tango::DeviceProxy &device, QString attrName){
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
        //*subWin[countDev].device
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
        subWin[countDev].scale = temp/100.0;
        subWin[countDev].setWindowTitle( subWin[countDev].windowTitle().split("scale").first() + QString("scale ") + ui->tlScaleRealTime->text());
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
    return image.scaled(image.width()*subWin[curDev].scale, image.height()*subWin[curDev].scale);
}

//Readin and displaying realtime data from the Tango server
//#threadArg - struct thread_data object, through it is send Mainwindon object (and more over in next version)
void MainWindow::startTesting(){    ///need in remaning!!!!!!
    int iter = 0;                       //current iteration of reading data from Tango Server //not used
    QTime time;
    QTime timeReadData;
    QPalette pal;
    time.start();
    fprintf(stderr, "==Starting Test==\n");
    Tango::DeviceAttribute attr;
    int local = 0;

    ////seting size of realtime display widget//////////
    attr = setTangoAttr(*subWin[local].device, subWin[local].attrName);
    fprintf(stderr,"--Time of--- readingData=%d\n", timeReadData.restart());

    setUCharVal(attr, subWin[local].val);

    subWin[local].dimX = attr.get_dim_x();
    subWin[local].dimY = attr.get_dim_y();
    subWin[countDev].resize(subWin[local].dimX/delim, subWin[local].dimY);
    //////////////////////////////////////////////////////

    while(subWin[local].work){
        ui->lbWork->setText("WORK");
        ui->lbWork->setPalette(QPalette(Qt::green));
        //ui->lbWork->setPalette(QPalette( isWork(0)));
        timeReadData.start();
        attr = setTangoAttr(*subWin[local].device, subWin[local].attrName);
        fprintf(stderr,"--Time of--- readingData=%d\n", timeReadData.restart());

        setUCharVal(attr, subWin[local].val);
        if (subWin[local].scale == 1.0){       //need in scaling???
                *subWin[local].img = QImage(&subWin[local].val[0],
                                                    attr.get_dim_x()/delim,
                                                    attr.get_dim_y(),
                                                    attr.get_dim_x(),
                                                    (QImage::Format )intColorFormat);
                subWin[local].wgt->resize(attr.get_dim_x()/delim, attr.get_dim_y());
            }
        else{
                *subWin[local].img = scaleImage(QImage(&subWin[local].val[0],
                                                                    attr.get_dim_x()/delim,
                                                                    attr.get_dim_y(),
                                                                    attr.get_dim_x(),
                                                                    (QImage::Format)intColorFormat));
                subWin[local].wgt->resize((attr.get_dim_x()/delim) * subWin[local].scale,
                                                  attr.get_dim_y() * subWin[local].scale);
            }
        pal.setBrush(subWin[local].wgt->backgroundRole(), QBrush(*subWin[local].img));
        subWin[local].wgt->setPalette(pal);
        fprintf(stderr,"x=%d y=%d\n",subWin[local].img->width(), subWin[local].img->height());
        fprintf(stderr,"iter=%d   -----devNum=%d ----- wholeTime=%d\n",iter, local, time.restart());
        subWin[local].repaint();
        QCoreApplication::processEvents(QEventLoop::AllEvents);    //Do System process
    }
    //ui->lbWork->setPalette(QPalette( isWork(1)));
    ui->lbWork->setText("NOT WORK");
    ui->lbWork->setPalette(QPalette(Qt::red));
}

//Init realtime reading data subwindow
void MainWindow::changeDevice(){
    subWin[countDev].setParent(this);
    subWin[countDev].wgt->setParent(this);

    snapshot->setEnabled(true);
    ui->btScaleRealTime->setEnabled(true);
    subWin[countDev].work = true;
    subWin[countDev].attrName = this->tangoDev->tlAttr->text();
    QString s;
    s =     (QString)"\/\/" + this->tangoDev->tlServer->text() +
            (QString)"\/" + tangoDev->tlDevice->text();
    fprintf(stderr,"!_%s_!\n", s.toAscii().constData());
    *subWin[countDev].device = addDevice(s);
    subWin[countDev].scrollArea->setWidget(subWin[countDev].wgt);
    subWin[countDev].scrollArea->move(100,100);
    subWin[countDev].scrollArea->resize(400, 300);
    subWin[countDev].scrollArea->show();
    subWin[countDev].resize(400, 300);
    subWin[countDev].numOfWin = countDev; /*need in Remaning*/
    subWin[countDev].isSnapshot = false;
    subWin[countDev].scale = ui->tlScaleRealTime->text().toDouble()/100;
    subWin[countDev].setWindowTitle(this->tangoDev->tlDevice->text() +
                                    QString(" scale ") + ui->tlScaleRealTime->text());
    area->hide();
    if (firstTime){
        QObject::connect(makeSnapshot, SIGNAL(triggered()), this, SLOT(mkSnapshot()));
        subWin[countDev].setWidget(subWin[countDev].scrollArea);
        area->addSubWindow(&subWin[countDev]);
    }
    subWin[countDev].scrollArea->resize(subWin[countDev].width()-2, subWin[countDev].height()-33);
    subWin[countDev].show();
    area->show();
    firstTime = false;
    ui->lbCurWorkiningDev->setText(QString("Cur Dev: ") + s + QString(" ") + tangoDev->tlAttr->text());

    ui->btChangeDevice->setEnabled(false);
    ui->btMkSnapshot->setEnabled(true);
    makeSnapshot->setEnabled(true);
    setDevice->setEnabled(false);
    pushCommand->setEnabled(true);

/*  Reading FLIP value
    bool flipHorizontal = true;
    bool flipVertical = true;
    setBoolVal(setTangoAttr(*subWin[countDev].device, (QString)"FlipHorizontal"), flipHorizontal);
    QVariant varValue(flipHorizontal);
    ui->lbFlipHorizontal->setText("FlipHorizontal " +  varValue.toString());//QString::number(flipHorizontal));
    setBoolVal(setTangoAttr(*subWin[countDev].device, (QString)"FlipVertical"), flipVertical);
    QVariant varValueV(flipVertical);
    ui->lbFlipVertical->setText("FlipVertical " + varValueV.toString());//QString::number(flipVertical));
*/

    tangoDev->close();
    delete tangoDev;
    startTesting();
}

