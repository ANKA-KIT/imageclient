#include <QtGui/QApplication>
#include "mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <my_device.h>

void print_usage(FILE * stream, int exitCode){
    fprintf(stream, "\n~~Usage: imageClient options are: \n");
    fprintf(stream,
            "-h  --help         Display Help \n"
            "-t  --tango_host   Set tango HOST. You can use TANGO_HOST system variable or set direct tango host\n"
            "-d  --device       Set tango device\n"
            "-a  --attr         Set image attribute\n"
            "-c  --command      Exec tango command before reading tango image data\n\n"
            "EXAMPLE: ./imageClient -tTANGO_HOST -dsys/tg_test/mytest -atestImage -cLoad16BitImg -cSetDataImage\n");
    exit(exitCode);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");
    MainWindow w;
    w.show();

    /////////////*deal with input options*//////////////
    int next_option;
    const char* const short_options  = "ht:d:a:c:";
    const struct option long_options[] = {
        {"help",            0, NULL, 'h'},
        {"tango_host",      1, NULL, 't'},
        {"device",          1, NULL, 'd'},
        {"attr",            1, NULL, 'a'},
        {"command",         1, NULL, 'c'},
        {NULL,              0, NULL,  0}
    };

    next_option = getopt_long(argc, argv, short_options, long_options, NULL);
    vector<QString> tangoCommands;
    QString attrName, devName, hostName;
    if(next_option != -1){
        while (next_option != -1){      //if no options
                    switch(next_option){
                    case 'h':{      //help
                        print_usage(stdout, 0);
                    }break;
                    case 't':{      //set tangoHost
                        //if env TANGO_HOST
                    if (strcmp(optarg, "TANGO_HOST") == 0){ //eql
                        hostName = QString(getenv("TANGO_HOST"));
                        //w.tangoDev->tlServer->setText(QString(getenv("TANGO_HOST")));
                    }
                    else{
                        hostName = QString(optarg);
                        //w.tangoDev->tlServer->setText(QString(optarg));
                    }
                    }break;
                    case 'd':{      //set device
                        devName = QString(optarg);
                         //w.tangoDev->tlDevice->setText(QString(optarg));
                    }break;
                    case 'a':{      //set attribute
                        attrName = QString(optarg);
                        // w.tangoDev->tlAttr->setText(QString(optarg));
                    }
                        break;
                    case 'c':{
                        tangoCommands.push_back(QString(optarg));
                    }
                        break;
                    case '?':{  //unknown symbol
                        print_usage(stderr, 1);
                    }
                    default: abort();
                    }
                    next_option = getopt_long(argc, argv, short_options, long_options, NULL);
         }

        if (hostName != "" && devName != "" && attrName != ""){

            w.initStartTangoWin();             //init rows for tango properties
            w.tangoDev->tlAttr->setText(attrName);
            w.tangoDev->tlDevice->setText(devName);
            w.tangoDev->tlServer->setText(hostName);
            my_Device dev;
            dev.initDevice(hostName, devName);
            for(int i=0; i<tangoCommands.size(); i++){
                fprintf(stderr, "Command: %s\n", tangoCommands.at(i).toAscii().constData());
                if (!dev.sendTangoCommand(tangoCommands.at(i))){
                   fprintf(stderr, "Command not set\n");
                }
            }
        }
        else{
            fprintf(stderr, "~~Put server, device, attribute info about tango device\n");
            print_usage(stdout, 1);
        }
    }
    return a.exec();
}
