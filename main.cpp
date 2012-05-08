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
            "-t  --tango_host   Set tango HOST\n"
            "-d  --device       Set tango device\n"
            "-a  --attr         Set image attribute\n"
            "-f  --file         Read deviceinfo from a XML file\n"
            "-c  --command      Exec tango command before reading tango image data\n");
    exit(exitCode);
}

int readFromFile(MainWindow &w, char *argv[]){
    fprintf(stderr, "Opening File\n");
    QDomDocument *doc = new QDomDocument();
    QFile *file = new QFile();
    fprintf(stderr, "FileName is %s\n", argv[1]);
    file->setFileName(QString(argv[1]));
    if (!file->open(QIODevice::ReadOnly)){
        fprintf(stderr, "FILE wasnot open\n");
        return 1;
    }
    if (!doc->setContent(file)){
        fprintf(stderr, "XML wasnot fill\n");
        file->close();
        return 1;
    }
    fprintf(stderr, "Opening File\n");
    file->close();
    QDomElement docElem = doc->documentElement();
    QDomNodeList nodeList = docElem.elementsByTagName("server").at(0).toElement().elementsByTagName("Type");
    if (nodeList.count() > 0)
    {
       int iDx;

       for(iDx = 0;iDx < nodeList.count(); iDx++){
           fprintf(stderr, "index num %d\n", iDx);
           fprintf(stderr, "server = %s\n", nodeList.at(iDx).attributes().namedItem("server").nodeValue().toAscii().constData());
           fprintf(stderr, "device = %s\n", nodeList.at(iDx).attributes().namedItem("device").nodeValue().toAscii().constData());
           fprintf(stderr, "attribute = %s\n", nodeList.at(iDx).attributes().namedItem("attribute").nodeValue().toAscii().constData());
           w.tangoDev->tlServer->setText(QString(nodeList.at(iDx).attributes().namedItem("server").nodeValue()));
           w.tangoDev->tlDevice->setText(QString(nodeList.at(iDx).attributes().namedItem("device").nodeValue()));
           w.tangoDev->tlAttr->setText(QString(nodeList.at(iDx).attributes().namedItem("attribute").nodeValue()));
       }
       w.changeDevice();
    }
    delete file;
    return 0;
}

int initSignals(MainWindow &w){
    QObject::connect(w.ui->btMkSnapshot, SIGNAL(clicked()), &w,SLOT(mkSnapshot()));
    QObject::connect(w.ui->btNewDev, SIGNAL(clicked()), &w,SLOT(setNewTangoDevice()));
    //QObject::connect(w.ui->btScale, SIGNAL(clicked()), &w,SLOT(scaleImage()));
    QObject::connect(w.ui->btChangeDevice, SIGNAL(clicked()), &w,SLOT(setTangoDevice()));

    QObject::connect(w.ui->btScaleRealTime, SIGNAL(clicked()), &w,SLOT(setRealtimeScale()));
    QObject::connect(w.ui->btScaleSnapshot, SIGNAL(clicked()), &w,SLOT(setSnapshotScale()));
    QObject::connect(w.ui->btWriteImg,SIGNAL(clicked()), &w,SLOT(saveImg()));
    //QObject::connect(w.ui->btChangeBrightness,SIGNAL(clicked()), &w,SLOT(changeBrightnessSnapshot()));
    return 0;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.move(0,0);
    w.setWindowTitle("Image Client");
    /////DeviceProxy("//anka-tango3.ka.fzk.de:10000/sys/tg_test/mytest");///////
    initSignals(w);
    w.area = new QMdiArea(&w);
    w.area->move(0,100);
    w.area->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    w.resize(1500, 600);
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
    if(next_option == -1){          //without commands options, but with parameters
        switch(argc){
            case ReadFromFile:{
                w.setTangoDevice();
                if(readFromFile(w, argv)){
                    fprintf(stderr,"Problems in reading from XML File");
                    exit(1);
                }
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
    else {                              // with options
        bool fromFile = false;          //is Info from a xml file
        w.setTangoDevice();             //init rows for tango properties
        QStringList tangoCommands;
        while (next_option != -1){      //if no options
            switch(next_option){
                case HELP:{                      //help
                    print_usage(stdout, 0);
                }
                    break;
                case TANGO_HOST:{               //set tangoHost
                    //if env TANGO_HOST
                    if (strcmp(optarg, "TANGO_HOST") == 0){ //eql
                        w.tangoDev->tlServer->setText(QString(getenv("TANGO_HOST")));
                    }
                    else{
                        w.tangoDev->tlServer->setText(QString(optarg));
                    }
                }
                    break;
                case DEVICE:{                  //set device
                     w.tangoDev->tlDevice->setText(QString(optarg));
                }
                    break;
                case ATTRIBUTE:{                  //set attribute
                     w.tangoDev->tlAttr->setText(QString(optarg));
                }
                    break;
                case FILE_NAME:{                  //read from file
                    if(readFromFile(w, argv)){
                        fprintf(stderr,"Problems in reading from XML File");
                        exit(1);
                    }
                    fromFile = true;
                }
                    break;
                case COMMAND:{                          //set command
                    tangoCommands<<QString(optarg);
                }
                    break;
                case UNKNOWN_SYMBOL:{                  //unknown symbol
                    print_usage(stderr, 1);
                }
                default:
                    abort();
            }

            if(!fromFile)
                next_option = getopt_long(argc, argv, short_options, long_options, NULL);
            else
                next_option = -1;
        }

        if(!fromFile){
            int i;
            if (w.tangoDev->tlServer->text() != "" && w.tangoDev->tlDevice->text() != "" && w.tangoDev->tlAttr->text() != ""){
                QString s;
                s =     (QString)"\/\/" + w.tangoDev->tlServer->text() +
                        (QString)"\/" + w.tangoDev->tlDevice->text();
                Tango::DeviceProxy *dev;
                *dev = w.addDevice(s);
                for(i=0; i<tangoCommands.count(); i++){
                    fprintf(stderr, "Command: %s\n", tangoCommands.at(i).toAscii().constData());
                    w.sendTangoCommand(dev, tangoCommands.at(i));
                }
                delete dev;
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
