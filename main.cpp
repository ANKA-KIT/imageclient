/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/
#include <QtGui/QApplication>
#include <QTime>
#include "mainwindow.h"
#include <ui_mainwindow.h>

#include <QtXml/QDomDocument>
#include <QtGui/QLabel>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
using namespace Tango;

void print_usage(FILE * stream, int exitCode){
    fprintf(stream, "Usage: TestApp options \n");
    fprintf(stream,
            "-h  --help         Display Help \n"
            "-t  --tango_host   Set tango HOST"
            "-d  --device       Set tango device"
            "-a  --attr         Set image attribute"
            "-f  --file         Read deviceinfo from a XML file"
            "-c  --command      Exec tango command before reading tango image data");
    exit(exitCode);
}

int main(int argc, char *argv[])
{
    enum StartParam {ReadFromFile = 2, LoadOneDevice = 4};
    QApplication a(argc, argv);
    MainWindow w;
    w.move(0,0);
    //w.device[0] = DeviceProxy("//anka-tango3.ka.fzk.de:10000/sys/tg_test/mytest"); //anka-tango3 //iss-vasilev

    QObject::connect(w.ui->btMkSnapshot, SIGNAL(clicked()), &w,SLOT(mkSnapshot()));
    QObject::connect(w.ui->btNewDev, SIGNAL(clicked()), &w,SLOT(setNewTangoDevice()));
    QObject::connect(w.ui->btScale, SIGNAL(clicked()), &w,SLOT(scaleImage()));
    QObject::connect(w.ui->btChangeDevice, SIGNAL(clicked()), &w,SLOT(setTangoDevice()));

    QObject::connect(w.ui->btScaleRealTime, SIGNAL(clicked()), &w,SLOT(setRealtimeScale()));
    QObject::connect(w.ui->btScaleSnapshot, SIGNAL(clicked()), &w,SLOT(setSnapshotScale()));
    QObject::connect(w.ui->btWriteImg,SIGNAL(clicked()), &w,SLOT(saveImg()));


    w.area = new QMdiArea(&w);
    w.area->move(0,100);
    w.area->resize(1000, 1000);

    w.area->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    w.resize(1300, 600);
    w.show();

    /////////////*deal with input options*//////////////
    int next_option;
    const char* const short_options  = "ht:d:a:f:c:";
    const struct option long_options[] = {
        {"help",            0, NULL, 'h'},
        {"tango_host",      1, NULL, 't'},
        {"device",          1, NULL, 'd'},
        {"attr",            1, NULL, 'a'},
        {"file",            1, NULL, 'f'},
        {"command",         1, NULL, 'c'},
        {NULL,              0, NULL,  0}
    };

    //get option
    next_option = getopt_long(argc, argv, short_options, long_options, NULL);
    if(next_option == -1){ //without commands options, but with parameters
        switch(argc){
            case ReadFromFile:{ // which casew?
            fprintf(stderr, "Opening File\n");
            QDomDocument *doc = new QDomDocument();
            QFile *file = new QFile();
            fprintf(stderr, "%s\n", argv[1]);
            file->setFileName(QString(argv[1]));
            if (!file->open(QIODevice::ReadOnly)){
                fprintf(stderr, "FILE wasnot open\n");
                exit(1);
            }
            if (!doc->setContent(file)){
                fprintf(stderr, "XML wasnot fill\n");
                file->close();
                exit(1);
            }
            fprintf(stderr, "Opening File\n");
            file->close();
            QDomElement docElem = doc->documentElement();
            QDomNodeList nodeList = docElem.elementsByTagName("server").at(0).toElement().elementsByTagName("Type");
            if (nodeList.count() > 0)
            {
               int iDx;
               w.setTangoDevice();
               for(iDx = 0;iDx < nodeList.count(); iDx++){
                   fprintf(stderr, "%d\n", iDx);
                   fprintf(stderr, "%s\n", nodeList.at(iDx).attributes().namedItem("server").nodeValue().toAscii().constData());
                   fprintf(stderr, "%s\n", nodeList.at(iDx).attributes().namedItem("device").nodeValue().toAscii().constData());
                   fprintf(stderr, "%s\n", nodeList.at(iDx).attributes().namedItem("attribute").nodeValue().toAscii().constData());
                   w.tangoDev->tlServer->setText(QString(nodeList.at(iDx).attributes().namedItem("server").nodeValue()));
                   w.tangoDev->tlDevice->setText(QString(nodeList.at(iDx).attributes().namedItem("device").nodeValue()));
                   w.tangoDev->tlAttr->setText(QString(nodeList.at(iDx).attributes().namedItem("attribute").nodeValue()));
               }
               w.changeDevice();
            }
            delete file;
            }
                break;
            case LoadOneDevice:{
                w.setTangoDevice();
                w.tangoDev->tlServer->setText(QString(argv[1]));
                w.tangoDev->tlDevice->setText(QString(argv[2]));
                w.tangoDev->tlAttr->setText(QString(argv[3]));
                fprintf(stderr,"STARTING\n");
                w.changeDevice();
                break;
            }
        default: break; // help function
        }
    }
    else {   // with options
        bool fromFile = false;
        w.setTangoDevice();             //init rows for tango properties
        while (next_option != -1){      //if no options
            switch(next_option){
            case 'h':{      //help
                print_usage(stdout, 0);
            }break;
            case 't':{      //set tangoHost
                //if env TANGO_HOST
                if (strcmp(optarg, "TANGO_HOST") == 0){ //eql
                    w.tangoDev->tlServer->setText(QString(getenv("TANGO_HOST")));
                }
                else{
                    w.tangoDev->tlServer->setText(QString(optarg));
                }
            }break;
            case 'd':{      //set device
                 w.tangoDev->tlDevice->setText(QString(optarg));
            }break;
            case 'a':{      //set attribute
                 w.tangoDev->tlAttr->setText(QString(optarg));
            }break;
            case 'f':{   //read from file
                fprintf(stderr, "Opening File\n");
                QDomDocument *doc = new QDomDocument();
                QFile *file = new QFile();
                fprintf(stderr, "%s\n", optarg);
                file->setFileName(QString(optarg));
                if (!file->open(QIODevice::ReadOnly)){
                    fprintf(stderr, "FILE wasnot open\n");
                    exit(1);
                }
                if (!doc->setContent(file)){
                    fprintf(stderr, "XML wasnot fill\n");
                    file->close();
                    exit(1);
                }
                fprintf(stderr, "Opening File\n");
                file->close();
                QDomElement docElem = doc->documentElement();
                QDomNodeList nodeList = docElem.elementsByTagName("server").at(0).toElement().elementsByTagName("Type");
                if (nodeList.count() > 0)
                {
                   int iDx;
                   for(iDx = 0;iDx < nodeList.count(); iDx++){
                       fprintf(stderr, "%d\n", iDx);
                       fprintf(stderr, "%s\n", nodeList.at(iDx).attributes().namedItem("server").nodeValue().toAscii().constData());
                       fprintf(stderr, "%s\n", nodeList.at(iDx).attributes().namedItem("device").nodeValue().toAscii().constData());
                       fprintf(stderr, "%s\n", nodeList.at(iDx).attributes().namedItem("attribute").nodeValue().toAscii().constData());
                       w.tangoDev->tlServer->setText(QString(nodeList.at(iDx).attributes().namedItem("server").nodeValue()));
                       w.tangoDev->tlDevice->setText(QString(nodeList.at(iDx).attributes().namedItem("device").nodeValue()));
                       w.tangoDev->tlAttr->setText(QString(nodeList.at(iDx).attributes().namedItem("attribute").nodeValue()));
                   }
                   fromFile = true;
                   w.changeDevice();
                }
            }break;
            case 'c':{
                w.tangoCommands<<QString(optarg);
            }break;
            case '?':{  //unknown symbol
                print_usage(stderr, 1);}
            default: abort();
            }

            if(!fromFile)
                next_option = getopt_long(argc, argv, short_options, long_options, NULL);
            else
                next_option = -1;
        }
        if(!fromFile){
            int i;
            if (w.tangoDev->tlServer->text() != "" && w.tangoDev->tlDevice->text() != "" && w.tangoDev->tlAttr->text() != ""){
            for(i=0; i<w.tangoCommands.count(); i++){
                fprintf(stderr, "Command: %s\n", w.tangoCommands.at(i).toAscii().constData());

           }
            w.changeDevice();   //exec tango device
            }
            else{
                fprintf(stderr, "Put server, device, attribute info about tango device\n");
                exit(1);
            }
        }
    }
    /////////////////////--------///////////////////////////////////
    return a.exec();
}
