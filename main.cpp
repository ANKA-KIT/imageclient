#include <QtGui/QApplication>
#include <QTime>
#include "mainwindow.h"
#include <ui_mainwindow.h>


#include <QtGui/QLabel>
#include <stdio.h>
#include <stdlib.h>
using namespace Tango;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fprintf(stderr,"NotMultiProc---%d\n", argc);
    MainWindow w;
    w.move(0,0);
    ///////////
    //w.device[0] = DeviceProxy("//anka-tango3.ka.fzk.de:10000/sys/tg_test/mytest"); //anka-tango3 //iss-vasilev
    w.countDev = 0;   // 1-in start
    w.countImg = 0;
    w.curImg = 0;
    w.curDev = 0;
    vector <unsigned char> valRead;
    char *proxy;
    char device[256];
    QTime writeTime;

    QObject::connect(w.ui->btMkSnapshot, SIGNAL(clicked()), &w,SLOT(mkSnapshot()));
    QObject::connect(w.ui->btNewDev, SIGNAL(clicked()), &w,SLOT(openDevInNewProc()));
    QObject::connect(w.ui->btScale, SIGNAL(clicked()), &w,SLOT(scaleImage()));
    QObject::connect(w.ui->btChangeDevice, SIGNAL(clicked()), &w,SLOT(changeDevice()));

    w.area = new QMdiArea(&w);
    w.area->move(0,100);
    w.area->resize(1000, 1000);

    w.area->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    w.resize(1300, 600);
    w.show();

    switch(argc){
        case (2):{
            QFile *file = new QFile(argv[1]);
            if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
               fprintf(stderr,"Cannot open file\n");
            }
            QTextStream in(file);
            QString *line = new QString();
                *line = in.readLine();
        //while (!line.isNull()) {
        //    process_line(line);
    //    proxy = //strdup((char *)(*line));
    //    *line = in.readLine();

        }
            break;
        case 4:{
        w.ui->tlServer->setText(QString(argv[1])); //serverName
        w.ui->tlDevice->setText(QString(argv[2]));
        w.ui->tlAttr->setText(argv[3]);
        fprintf(stderr,"STARTING\n");
        w.changeDevice();
//        QObject::connect(&w, SIGNAL(activated(int )), &w, SLOT(changeDevice()));
        break;
        }
    default: break;
    }

    return a.exec();
}
