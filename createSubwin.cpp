#include "mainwindow.h"
#include "ui_mainwindow.h"

//Init realtime reading data subwindow
void MainWindow::changeDevice(){
    subWin[countDev].setParent(this);
    subWin[countDev].wgt->setParent(this);

    snapshot->setEnabled(true);
    ui->btScaleRealTime->setEnabled(true);
    subWin[countDev].work = true;
    subWin[countDev].attrName = this->tangoDev->tlAttr->text();
    QString s;
    s = (QString)"\/\/" + this->tangoDev->tlServer->text() + (QString)"\/";
    s += this->tangoDev->tlDevice->text();
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
    thread_data data;
    data.parent = this;
    data.threadNum = subWin[countDev].numOfWin;
    fprintf(stderr, "\n=----%p----=%d\n", data.parent, subWin[countDev].numOfWin);
    ui->lbCurWorkiningDev->setText(QString("Cur Dev: ") + s + QString(" ") + tangoDev->tlAttr->text());

    ui->btChangeDevice->setEnabled(false);
    ui->btMkSnapshot->setEnabled(true);
    makeSnapshot->setEnabled(true);
    setDevice->setEnabled(false);
    pushCommand->setEnabled(true);

    tangoDev->close();
    startTesting((void*) &data);
}

