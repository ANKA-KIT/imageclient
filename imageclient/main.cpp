#include <QApplication>
#include "mainwindow.h"
#include <argtable/src/argtable2.h>
#include <etangodevice.h>

/*!
  imageClient - Qt application for dealing with ANKA photo-cameras, based on TANGO
  Developed by Georgii Vasilev TPU (TOMSK POLYTECHNIC UNIVERITY) for KIT
  E-Mail: georgy13@mail.ru
*/

void print_usage(FILE * stream, int exitCode){
    fprintf(stream,"\nImageClient - Qt application for dealing with ANKA photo-cameras, based on TANGO."
            "ImageClient allows set Contrast, Gamma, Brightness, Rotation, Scale, Horizontal and Vertical flipping for getting picture from TANGO photo-cameras. "
            "Application also allows to make a snapshot, does some manipulations with picture and save it, send a Tango command."
            "Application has opportunity to deal with Server variables which are answer for image properties and read Tango device static info.\n");
    fprintf(stream, "\n~~Usage: imageClient options are: \n");
    fprintf(stream,
            "-h  --help         Display Help \n"
            "--delay-time=<int> Set in miliseconds time on Delay on getting new picture\n"
            "-t  --tango_host   Set tango HOST.\n"
            "-d  --device       Set tango device\n"
            "-a  --attr         Set image attribute\n"
            "-c  --command      Exec tango command before reading tango image data\n"
            "-m  --imagemode    Set imageMode for correct displaying Image in a start\n"
            "  -m0            IS_16BITGRAY.  It is 16 bit greyscale  image mode \n"
            "  -m1            IS_RGB.        It is RGB color image mode \n"
            "  -m2            IS_48BIT.      It is 16 bit RGB  image mode \n"
            "  -m3            IS_RGBGRAY.    It is RGB greyscale image mode \n"
            "  -m4            IS_8BIT.       It is 8 bit greyscale  image mode \n"
            "  -m5            IS_RGBA.       It is 8 bit RGBA  image mode \n"
            "EXAMPLE: ./imageClient -tanka-tango3.ka.fzk.de:10000 -dsys/tg_test/mytest -atestImage -cLoad16BitImg -cSetDataImage -m2  --delay-time=1000 \n"
            );
    exit(exitCode);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.addLibraryPath("./plugins");
    vector<QString> tangoCommands;
    QString attrName, devName, hostName;
    int imMode = -1;
    bool startWithParams = false;
    bool withAttrs = false;
    bool isImModeSet = false;

    struct arg_lit  *help    = arg_lit0("h","help", "print this help and exit");
    struct arg_int  *delaytime = arg_int0(NULL,"delay-time","<int>", "Set in miliseconds time on Delay on getting new picture\n");
    struct arg_int  *imagemode = arg_int0("m","imagemode","<int>", "Set imageMode for correct displaying Image in a start\n");
    struct arg_str  *tangohost = arg_str0("t", "tango_host", NULL,    "Set tango HOST. \n");
    struct arg_str  *tangodevice = arg_str0("d", "device", NULL,    "Set tango device\n");
    struct arg_str  *tangoattr = arg_str0("a", "attr", NULL,    "Set tango image attribute\n");
    struct arg_str  *tangocommand = arg_strn("c", "command", NULL,0, 999,    "Exec tango command before reading tango image data\n");
    struct arg_end  *end = arg_end(20);
    void* argtable[] = {delaytime,tangocommand, tangoattr, tangodevice, tangohost, imagemode, help, end};

    /* verify the argtable[] entries were allocated sucessfully */
    if (arg_nullcheck(argtable) != 0) {
        /* NULL entries were detected, some allocations must have failed */
        fprintf(stderr, ": insufficient memory\n");
        print_usage(stderr, 1);
    }
    int nerrors = arg_parse(argc, argv, argtable);
    if (nerrors > 0){
        const char *progname = "imageClient";
            /* Display the error details contained in the arg_end struct.*/
            arg_print_errors(stderr, end, progname);
            print_usage(stderr, 1);
    }
    if (help->count > 0){
        print_usage(stdout, 0);
    }
    if (delaytime->count > 0){
        w.startDelayTime = delaytime->ival[0];
    }
    if (tangoattr->count > 0) {
        withAttrs = true;
        attrName = QString(tangoattr->sval[0]);
    }
    if (tangodevice->count > 0) {
        withAttrs = true;
        devName = QString(tangodevice->sval[0]);
    }
    if (tangohost->count > 0) {
        withAttrs = true;
        hostName = QString(tangohost->sval[0]);
    }
    if (imagemode->count > 0) {
        imMode = imagemode->ival[0];
        if (imMode >= -1 && imMode <= 5) {
            isImModeSet = true;
            startWithParams = true;
        }
        else{
            fprintf(stderr, "SET correct IMAGE MODE (-m) value\n");
            print_usage(stderr, 1);
        }
    }
    for (int i=0; i<tangocommand->count; i++){
        tangoCommands.push_back(QString(tangocommand->sval[i]));
    }
    if (withAttrs){
        if (tangoattr->count > 0 && tangodevice->count > 0 && tangohost->count > 0){// &&hostName != "" && devName != "" && attrName != ""){
            /* Open and fill startTangoWin */
            TDevice *dev = new TDevice(&a);
            if (dev->device()->checkAttr(hostName + "/" + devName, attrName)) {
                w.chooseDevice();
                w.startTWin->tlAttr->setText(attrName);
                w.startTWin->tlDevice->setText(devName);
                w.startTWin->tlServer->setText(hostName);
                for (size_t i = 0; i < tangoCommands.size(); i++){
                    fprintf(stderr, "Command: %s\n", tangoCommands.at(i).toAscii().constData());
                    dev->setSource("//"+hostName+"/"+devName,"");
                    if (!dev->sendTangoCommand(tangoCommands[i])){
                        fprintf(stderr, "Command not set\n");
                    }
                }
                /* setting imageMode */
                if (startWithParams) {
                    if (isImModeSet) {
                        w.startImageMode = imMode;
                    }
                }
                w.startTWin->onOk();
            } else {
                fprintf(stderr, "~~Device not available or you set incorrect Host or Device or Attribute name\n");
                print_usage(stdout, 1);
            }
            delete dev;
        } else {
            fprintf(stderr, "~~Put SERVER, DEVICE and ATTRIBUTE info about tango device (-t -d -a attribute must be set)\n");
            print_usage(stdout, 1);
        }
    }
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    w.show();
    return a.exec();
}
