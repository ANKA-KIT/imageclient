#include <QtGui/QApplication>
#include "mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <my_device.h>

void print_usage(FILE * stream, int exitCode){
    fprintf(stream,"ImageClient - Qt application for dealing with ANKA photo-cameras, based on TANGO."
            "ImageClient allows set Contrast, Gamma, Brightness, Rotation, Scale, Horizontal and Vertical flipping for getting picture from TANGO photo-cameras. "
            "Application also allows to make a snapshot, does some manipulations with picture and save it, send a Tango command."
            "Application has opportunity to deal with Server variables which are answer for image properties and read Tango device static info.\n");
    fprintf(stream, "\n~~Usage: imageClient options are: \n");
    fprintf(stream,
            "-h  --help         Display Help \n"
            "-t  --tango_host   Set tango HOST. You can use TANGO_HOST system variable or set direct tango host\n"
            "-d  --device       Set tango device\n"
            "-a  --attr         Set image attribute\n"
            "-c  --command      Exec tango command before reading tango image data\n"
            "-m  --imagemode    Set imageMode for correct displaying Image in a strt\n"
            "  -m0            IS_16BITIMG_GREY. It is 16 bit greyscale  image mode \n"
            "  -m1            IS_RGBIMG_GREY.   It is RGB greyscale image mode \n"
            "  -m2            IS_RGBIMG_COLOR.  It is RGB color image mode \n"
            "  -m3            IS_8BITIMG_GREY.  It is 8 bit greyscale  image mode \n"
            "  -m4            IS_8BITIMG_COLOR. It is 8 bit color image mode \n"
            "  -m5            IS_16BITIMG_RGB.  It is 16 bit RGB  image mode \n"
            "-f  --imageformat  Qt stuff setting for correct setting image in image Modes (-m)\n"
            "  -f3            ImageFormatIndex8;      The image is stored using 8-bit indexes into a colormap.\n"
            "  -f4            ImageFormatRGB32;       The image is stored using a 32-bit RGB format (0xffRRGGBB).\n"
            "  -f5            ImageFormatARGB32;      The image is stored using a 32-bit ARGB format (0xAARRGGBB).\n"
            "  -f6            ImageFormatARGB32Pre;   The image is stored using a premultiplied 32-bit ARGB format (0xAARRGGBB),"
                                                        "i.e. the red, green, and blue channels are multiplied by the alpha component divided by 255."
                                                        " (If RR, GG, or BB has a higher value than the alpha channel, the results are undefined.) "
                                                        "Certain operations (such as image composition using alpha blending) are faster using premultiplied ARGB32 than with plain ARGB32.\n"
            "  -f7            ImageFormatRGB16;       The image is stored using a 16-bit RGB format (5-6-5).\n"
            "  -f8            ImageFormatARGB8565Pre; The image is stored using a premultiplied 24-bit ARGB format (8-5-6-5).\n"
            "  -f9            ImageFormatRGB666;      The image is stored using a 24-bit RGB format (6-6-6). The unused most significant bits is always zero.\n"
            "  -f10           ImageFormatARGB6666Pre; The image is stored using a premultiplied 24-bit ARGB format (6-6-6-6).\n"
            "  -f11           ImageFormatRGB555;      The image is stored using a 16-bit RGB format (5-5-5). The unused most significant bit is always zero.\n"
            "  -f12           ImageFormatARGB8555Pre; The image is stored using a premultiplied 24-bit ARGB format (8-5-5-5).\n"
            "  -f13           ImageFormatRGB888;      The image is stored using a 24-bit RGB format (8-8-8).\n"
            "  -f14           ImageFormatRGB444;      The image is stored using a 16-bit RGB format (4-4-4). The unused bits are always zero.\n"
            "  -f15           ImageFormatARGB4444Pre; The image is stored using a premultiplied 16-bit ARGB format (4-4-4-4).\n\n"

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
    const char* const short_options  = "ht:d:a:c:f:m:";
    const struct option long_options[] = {
        {"help",            0, NULL, 'h'},
        {"tango_host",      1, NULL, 't'},
        {"device",          1, NULL, 'd'},
        {"attr",            1, NULL, 'a'},
        {"command",         1, NULL, 'c'},
        {"imagemode",         1, NULL, 'm'},
        {"imageformat",         1, NULL, 'f'},
        {NULL,              0, NULL,  0}
    };

    next_option = getopt_long(argc, argv, short_options, long_options, NULL);
    vector<QString> tangoCommands;
    QString attrName, devName, hostName;
    int imFormat = -1, imMode = -1;
    bool ok, isImModeSet=false, isImFormatSet=false;
    if(next_option != -1){
        while (next_option != -1){      //if no options
                    switch(next_option){
                        case 'h':      //help
                            print_usage(stdout, 0);
                        break;
                        case 't':      //set tangoHost
                            //if env TANGO_HOST
                        if (strcmp(optarg, "TANGO_HOST") == 0){ //eql
                            hostName = QString(getenv("TANGO_HOST"));
                            //w.tangoDev->tlServer->setText(QString(getenv("TANGO_HOST")));
                        }
                        else{
                            hostName = QString(optarg);
                            //w.tangoDev->tlServer->setText(QString(optarg));
                        }
                        break;
                        case 'd':      //set device
                            devName = QString(optarg);
                             //w.tangoDev->tlDevice->setText(QString(optarg));
                        break;
                        case 'a':      //set attribute
                            attrName = QString(optarg);
                            // w.tangoDev->tlAttr->setText(QString(optarg));
                        break;
                        case 'c':
                            tangoCommands.push_back(QString(optarg));
                        break;
                        case 'f':
                            ok = true;
                            imFormat = QString(optarg).toInt(&ok);
                            if (!ok && (imFormat-4>=-1 && imFormat-4 <= 11)){
                                fprintf(stderr, "SET correct IMAGE FORMAT (-f) value");
                                print_usage(stderr, 1);
                            }
                            isImFormatSet = true;
                            w.startWithParams = true;
                        break;
                        case 'm':
                            ok = true;
                            imMode = QString(optarg).toInt(&ok);
                            if (!ok && (imMode >= -1 || imMode <= 5)){
                                fprintf(stderr, "SET correct IMAGE MODE (-m) value");
                                print_usage(stderr, 1);
                            }
                            isImModeSet = true;
                            w.startWithParams = true;
                        break;
                        case '?':  //unknown symbol
                            print_usage(stderr, 1);
                        break;
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
            if (w.startWithParams){
                if(isImFormatSet){
                    w.startImageFormat = new int();
                    *w.startImageFormat = imFormat;
                }
                if(isImModeSet){
                    w.startImageMode = new int();
                    *w.startImageMode = imMode;
                }
            }
            w.tangoDev->onOk();
        }
        else{
            fprintf(stderr, "~~Put server, device, attribute info about tango device\n");
            print_usage(stdout, 1);
        }
    }
    return a.exec();
}
