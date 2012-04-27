#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "changeBrightness.h"



//set Snapshot Scale value
void MainWindow::setSnapshotScale(){
    bool ok = true;
    double temp;
    fprintf(stderr, "Snapshot scaling\n");
        temp = ui->tlScaleSnapshot->text().toDouble(&ok); //Ok??????
        if (ok){
 //           *subWinSnapPointer->img = changeBrightness(*subWinSnapPointer->img, 10);
            subWinSnapPointer->scale = temp/100.0;
            scaleImage();
            subWinSnapPointer->setWindowTitle(subWinSnapPointer->windowTitle().split("scale").first() + QString("scale ") + ui->tlScaleSnapshot->text());
        }
        else{
            fprintf(stderr, "Put correct number to the Snapshot scale line");
            exit(1);
        }
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

//save current snapshot
void MainWindow::saveImg(){
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(
              this,
              tr("Save Snapshot"),
              QDir::currentPath(),
                  tr("JPG(*.jpg);; TIFF(*.tiff);; BMP(*.bmp);; PNG(*.png);; JPEG(*jpeg);;"
                                "XBM(*.xbm);; XPM(*.xpm);; PPM(*.ppm)"),
                 &selectedFilter);
    if(filename != ""){
        QString f = QString("./") + filename.split("\/").last() +
                QString(".") + selectedFilter.split("(").takeFirst().toLower();
        fprintf(stderr, "save Format %s\n",  selectedFilter.split("(").takeFirst().toLower().toAscii().constData());
        subWinSnapPointer->img->save(f, selectedFilter.split("(").takeFirst().toAscii().constData());
        fprintf(stderr, "Save an Image\n");
    }
    else
        fprintf(stderr, "Saving an Image is canceled\n");
}

//make a snapshot
void MainWindow::mkSnapshot(){
    ui->btScale->setEnabled(true);
    ui->btWriteImg->setEnabled(true);
    saveSnapshot->setEnabled(true);
    ui->btScaleSnapshot->setEnabled(true);
    ui->btChangeBrightness->setEnabled(true);

    QPalette pal;
    SubWindow *tempSubWinSnapPointer = new SubWindow();
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
    tempSubWinSnapPointer->wgt->resize(subWin[curDev].dimX/delim, subWin[curDev].dimY);

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

    countImg++;
}
