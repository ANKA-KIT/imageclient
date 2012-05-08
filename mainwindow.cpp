/*
    Author: Georgii Vasilev
    Project: Image client
    Aprel 2012
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QPainter>

//#include "changeBrightness.h"

#include <QImage>
#include "math.h"

///////////http://www.qtforum.org/article/26907/contrast-transparency-brightness.html////////////////////////
template<class T>
inline const T& kClamp( const T& x, const T& low, const T& high )
{
    if ( x < low )       return low;
    else if ( high < x ) return high;
    else                 return x;
}

inline
int changeBrightness( int value, int brightness )
    {
    return kClamp( value + brightness * 255 / 100, 0, 255 );
    }

inline
int changeContrast( int value, int contrast )
    {
    return kClamp((( value - 127 ) * contrast / 100 ) + 127, 0, 255 );
    }

inline
int changeGamma( int value, int gamma )
    {
    return kClamp( int( pow( value / 255.0, 100.0 / gamma ) * 255 ), 0, 255 );
    }

inline
int changeUsingTable( int value, const int table[] )
    {
    return table[ value ];
    }

template< int operation( int, int ) >
static
QImage changeImage( const QImage& image, int value )
    {
    QImage im = image;
    im.detach();
    if( im.numColors() == 0 ) /* truecolor */
        {
        if( im.format() != QImage::Format_RGB32 ) /* just in case */
            im = im.convertToFormat( QImage::Format_RGB32 );
        int table[ 256 ];
        for( int i = 0;
             i < 256;
             ++i )
            table[ i ] = operation( i, value );
        if( im.hasAlphaChannel() )
            {
            for( int y = 0;
                 y < im.height();
                 ++y )
                {
                QRgb* line = reinterpret_cast< QRgb* >( im.scanLine( y ));
                for( int x = 0;
                     x < im.width();
                     ++x )
                    line[ x ] = qRgba( changeUsingTable( qRed( line[ x ] ), table ),
                        changeUsingTable( qGreen( line[ x ] ), table ),
                        changeUsingTable( qBlue( line[ x ] ), table ),
                        changeUsingTable( qAlpha( line[ x ] ), table ));
                }
            }
        else
            {
            for( int y = 0;
                 y < im.height();
                 ++y )
                {
                QRgb* line = reinterpret_cast< QRgb* >( im.scanLine( y ));
                for( int x = 0;
                     x < im.width();
                     ++x )
                    line[ x ] = qRgb( changeUsingTable( qRed( line[ x ] ), table ),
                        changeUsingTable( qGreen( line[ x ] ), table ),
                        changeUsingTable( qBlue( line[ x ] ), table ));
                }
            }
        }
    else
        {
        QVector<QRgb> colors = im.colorTable();
        for( int i = 0;
             i < im.numColors();
             ++i )
            colors[ i ] = qRgb( operation( qRed( colors[ i ] ), value ),
                operation( qGreen( colors[ i ] ), value ),
                operation( qBlue( colors[ i ] ), value ));
        }
    return im;
    }

// brightness is multiplied by 100 in order to avoid floating point numbers
QImage changeBrightness( const QImage& image, int brightness )
    {
    if( brightness == 0 ) // no change
        return image;
    return changeImage< changeBrightness >( image, brightness );
    }


// contrast is multiplied by 100 in order to avoid floating point numbers
QImage changeContrast( const QImage& image, int contrast )
    {
    if( contrast == 100 ) // no change
        return image;
    return changeImage< changeContrast >( image, contrast );
    }

// gamma is multiplied by 100 in order to avoid floating point numbers
QImage changeGamma( const QImage& image, int gamma )
    {
    if( gamma == 100 ) // no change
        return image;
    return changeImage< changeGamma >( image, gamma );
    }

////////////////////////////////////////////////////////////////////////////////////////
QImage MainWindow::chBrightness(QImage& image, int brightness ){
    return changeBrightness(image, brightness );
}
QImage MainWindow::chContrast(QImage& image, int brightness ){
    return changeContrast(image, brightness );
}
QImage MainWindow::chGamma(QImage& image, int brightness ){
    return changeGamma(image, brightness );
}


//
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{

}

void CommandLine::closeEvent ( QCloseEvent * closeEvent){
    //delete this
}

void TangoProperties::closeEvent ( QCloseEvent * closeEvent){

}

//Destructor of mainwindow
MainWindow::~MainWindow(){
        fprintf(stderr,"---!_in mainwinDestructor\n");

        delete setDevice;                 //set for current app tango device
        delete addNewDevice;              //set tango device in new app
        delete pushCommand;               //set tango command
        delete exitAct;                   //Stop app

        delete makeSnapshot;              //Make snapshot
        delete saveSnapshot;              //Save current snapshot

        delete snapshot;
        delete server;
        delete realtime;

        delete scaleRealtime;
        delete setBrightnessRealtime;
        delete setContrastRealtime;
        delete setGammaRealtime;
        delete setRotationRealtime;
        delete verFlipRealtime;
        delete horFlipRealtime;
        delete resetImgRealtime;
fprintf(stderr,"---!\n");
        delete setImageFormatIndex8;
        delete setImageFormatRGB32;
        delete setImageFormatARGB32;
        delete setImageFormatARGB32Pre;
        delete setImageFormatRGB16;
        delete setImageFormatARGB8565Pre;
        delete setImageFormatRGB666;
        delete setImageFormatARGB6666Pre;
        delete setImageFormatRGB555;
        delete setImageFormatARGB8555Pre;
        delete setImageFormatRGB888;
        delete setImageFormatRGB444;
        delete setImageFormatARGB4444Pre;

        delete scaleSnapshot;             //scale current snapshot  //not used
        delete horFlipSnapshot;
        delete verFlipSnapshot;
        delete setBrightnessSnapshot;
        delete setContrastSnapshot;
        delete setGammaSnapshot;
        delete setRotationSnapshot;
//        delete resetImgSnapshot;

        delete area;
        fprintf(stderr,"---!\n");
        delete ui;
        fprintf(stderr,"---!_Delete Mainwin in   destructor_!\n");
}

//Destructor of subwindow
SubWindow::~SubWindow(){
    delete device;
    delete img;
    delete imgOrigin;
    delete wgt;
    delete scrollArea;
    fprintf(stderr,"---!_Delete SubWinexport TANGO_HOST=anka-tango3.ka.fzk.de:10000 in _ destructor_!\n");

}

//on close mainwindow
void MainWindow::closeEvent ( QCloseEvent * closeEvent){
    subWin->setAttribute(Qt::WA_DeleteOnClose);
    if  (subWin[0].work){//subWin[0].isActiveWindow()){// isActiveWindow())//isHidden()

      subWin[0].close();
    }
    if(tangoDev != NULL){
        delete tangoDev;
    }
    if(cmdTangoLine != NULL){
        delete cmdTangoLine;
    }
    if(vSetting != NULL){
        delete vSetting;
    }
    fprintf(stderr,"is_SubWin_ActiveWindow: %d\n", subWin[0].isActiveWindow());
    this->~MainWindow();        ///????????????????????????
    exit(0); /////////why app don't stop without this command?????????
}

//inital window for setting command for sending it to tango device
void MainWindow::setTangoCommand(){
    if (cmdTangoLine != NULL){
        fprintf(stderr, "!!!!!!!was!!!Qt::WA_DeleteOnClose !!!but !!!!!!!!!'tangoDev != NULL'!!!!!!!!!!!!!!\n");
        delete cmdTangoLine;
        cmdTangoLine = NULL;

    }
    if (cmdTangoLine == NULL){
        cmdTangoLine = new CommandLine(this);
        cmdTangoLine->setWindowModality(Qt::ApplicationModal);
       // cmdTangoLine->setAttribute(Qt::WA_DeleteOnClose);     //!!!!!!!!! use upper IF to delete object !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        QObject::connect(cmdTangoLine->btCancel, SIGNAL(clicked()), this, SLOT(cancelCommandLine()));
        QObject::connect(cmdTangoLine->btSend, SIGNAL(clicked()), this, SLOT(sendTangoCommandSLOT()));
        cmdTangoLine->show();
    }
    else{
        fprintf(stderr, "cmdTangoLine is inited\n");
        exit(1);
    }
}

//exec sending tango command
void MainWindow::sendTangoCommandSLOT(){
    sendTangoCommand(subWin->device, cmdTangoLine->tlCommand->text());
    cmdTangoLine->close();
    delete cmdTangoLine;
    cmdTangoLine = NULL;
}

//start window Tango device property
void MainWindow::setTangoDevice(){ ///use one more slot!!!!!!
    tangoDeviceWin();
    QObject::connect(tangoDev->btChangeDevice, SIGNAL(clicked()), this, SLOT(changeDevice()));
    tangoDev->btNewDev->setEnabled(false);
    tangoDev->btChangeDevice->setEnabled(true);
}

//inital window for setting attributes for starting tango device
void MainWindow::tangoDeviceWin(){
    if (tangoDev != NULL){
        fprintf(stderr, "!!!!!!!was!!!Qt::WA_DeleteOnClose !!!but !!!!!!!!!'tangoDev != NULL'!!!!!!!!!!!!!!\n");
        delete tangoDev;
        tangoDev = NULL;

    }
    if (tangoDev == NULL){
        tangoDev = new TangoProperties(this);
        tangoDev->setWindowModality(Qt::ApplicationModal);
        //tangoDev->setAttribute(Qt::WA_DeleteOnClose);  //!!!!!!!!! use upper IF to delete object!!!!!!!!!!!!!!!!!!!!!!!!!
        QObject::connect(tangoDev->btCancel, SIGNAL(clicked()), this, SLOT(cancelTangoProperties()));
        tangoDev->show();

    }
    else{
        fprintf(stderr, "tangoDev is inited\n");
        exit(1);
    }
}

//inital window for setting attributes for starting tango device in new window
void MainWindow::setNewTangoDevice(){
    tangoDeviceWin();
    QObject::connect(tangoDev->btNewDev, SIGNAL(clicked()), this, SLOT(openDevInNewProc()));
    tangoDev->btChangeDevice->setEnabled(false);
    tangoDev->btNewDev->setEnabled(true);
}

//Set parent widget for subwindow
void SubWindow::setParent(MainWindow *p){
    parent = p;
}
void ImageWidget::setParent(MainWindow *p){
    parent = p;
}

//seting the color of label "is device work"
int MainWindow::isWork(int status){
    switch(status){
        case Work:{
           // pal.setColor(this->ui->lbWork->backgroundRole(), QColor().green());
            ui->lbWork->setText("Work");
            return (int)QColor().green();//pal;
        }break;
        case DevNotSet:{
            //pal.setColor(this->ui->lbWork->backgroundRole(), QColor().red());
            ui->lbWork->setText("NOT WORK");
            fprintf(stderr, "set LbWork %d\n", Qt::red);
            return Qt::red;//pal;
        }break;
        case Error:{
           // pal.setColor(this->ui->lbWork->backgroundRole(), QColor().red());
            ui->lbWork->setText("NOT WORK");
            return QColor().red();//pal;
        }break;
    default: return Qt::red;//{pal.setColor(this->ui->lbWork->backgroundRole(), QColor().blue()); return pal;}
    }
}

int initcmbColorFormat(MainWindow &w){
    QStringList ls;
    ls  <<"QImage::Format_Indexed8"
        <<"QImage::Format_RGB32"
        <<"QImage::Format_ARGB32"
        <<"QImage::Format_ARGB32_Premultiplied"
        <<"QImage::Format_RGB16"
        <<"QImage::Format_ARGB8565_Premultiplied"
        <<"QImage::Format_RGB666"
        <<"QImage::Format_ARGB6666_Premultiplied"
        <<"QImage::Format_RGB555"
        <<"QImage::Format_ARGB8555_Premultiplied"
        <<"QImage::Format_RGB888"
        <<"QImage::Format_RGB444"
        <<"QImage::Format_ARGB4444_Premultiplied";
    w.ui->cmbColorFormat->addItems(ls);
    w.intColorFormat = QImage::Format_RGB32; //value int 4;
    w.ui->cmbColorFormat->setCurrentIndex(1); ////value QImage::Format_RGB32
    w.colorFormat = "QImage::Format_RGB32";
    w.delim = 4;
    QObject::connect(w.ui->cmbColorFormat, SIGNAL(currentIndexChanged(int)), &w, SLOT(changeColorFormat(int)));
}


int initcmbRotate(MainWindow &w){
    QStringList lsGrad;
    lsGrad << "0"<<"90"<<"180"<<"270"
           <<"-90"<<"-180"<<"-270";

    w.ui->cmbRotate->addItems(lsGrad);
    w.ui->cmbRotate->setCurrentIndex(0);      //val 0 degree
    QObject::connect(w.ui->cmbRotate, SIGNAL(currentIndexChanged(int)), &w, SLOT(rotateImg(int)));
}

void MainWindow::setEnabledSnapshot(bool isEnable){
    if(isEnable){
        ui->btWriteImg->setEnabled(true);
        saveSnapshot->setEnabled(true);
        ui->btScaleSnapshot->setEnabled(true);
        //ui->btChangeBrightness->setEnabled(true);
        ui->cmbRotate->setEnabled(true);
        //ui->cmbFlipHor->setEnabled(true);
       // ui->cmbFlipVer->setEnabled(true);
        horFlipSnapshot->setEnabled(true);
        verFlipSnapshot->setEnabled(true);
        //ui->btScale->setEnabled(true);
        setBrightnessSnapshot->setEnabled(true);
        setContrastSnapshot->setEnabled(true);
        setGammaSnapshot->setEnabled(true);
        scaleSnapshot->setEnabled(true);
        setRotationSnapshot->setEnabled(true);
    }
    else{
         //ui->btScale->setEnabled(false);
         ui->btScaleSnapshot->setEnabled(false);
         ui->cmbRotate->setEnabled(false);
        // ui->cmbFlipHor->setEnabled(false);
        // ui->cmbFlipVer->setEnabled(false);
         horFlipSnapshot->setEnabled(false);
         verFlipSnapshot->setEnabled(false);
         ui->btWriteImg->setEnabled(false);
         //ui->btChangeBrightness->setEnabled(false);
         saveSnapshot->setEnabled(false);
         setBrightnessSnapshot->setEnabled(false);
         setContrastSnapshot->setEnabled(false);
         setGammaSnapshot->setEnabled(false);
         scaleSnapshot->setEnabled(false);
         setRotationSnapshot->setEnabled(false);
    }
}

//Constructor of main window
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    countImg = 0;
    curImg = 0;
    createActions();
    createMenu();
    subWin = new SubWindow();
    if (!subWin){
        fprintf(stderr, "Error in MainWin constructor: init subWin \n");
        exit(1);
    }
    subWin->work = false;
    firstTime = true;

    ui->btMkSnapshot->setEnabled(false);
    ui->btScaleRealTime->setEnabled(false);

    QObject::connect(subWin,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),
                     subWin,SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates)));

    initcmbColorFormat(*this);
    initcmbRotate(*this);
    //ui->cmbFlipHor->addItems(QStringList()<<"False"<<"True");
    //ui->cmbFlipVer->addItems(QStringList()<<"False"<<"True");

    //QObject::connect(ui->cmbFlipHor, SIGNAL(currentIndexChanged(int)), this, SLOT(setFlipHor(int)));
    //QObject::connect(ui->cmbFlipVer, SIGNAL(currentIndexChanged(int)), this, SLOT(setFlipVer(int)));


    ui->lbWork->setAutoFillBackground(true);
    ui->lbWork->setPalette(QPalette(Qt::red));

    tangoDev = NULL;
    cmdTangoLine = NULL;
    setEnabledSnapshot(false);
    realtime->setEnabled(false);
    vSetting = NULL;
}

//Constructor of subwindow  //overloaded
SubWindow::SubWindow(QWidget *parent, Qt::WindowFlags flags){
    device = new  Tango::DeviceProxy();
    wgt = new ImageWidget();
    scrollArea = new QScrollArea();
    img = new QImage();
    imgOrigin = new QImage();
    verFlip = false;
    horFlip = false;
    contrast = 100;
    brightness = 0;
    gamma = 100;
    rotation = 0;
    scrollArea->hide();
    scrollArea->setWindowModality(Qt::WindowModal);
    scrollArea->resize(800, 500);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->move(50, 100);
    wgt->setAutoFillBackground(true);
    wgt->setMouseTracking(true);
    this->setAutoFillBackground(true);

    QObject::connect(this,SIGNAL(windowStateChanged(Qt::WindowStates,Qt::WindowStates )),this,
                    SLOT(handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates )));
}

//set Vertical Flip
void MainWindow::setFlipVer(){
    QImage tempImg;
    QPalette pal;
    subWinSnapPointer->wgt->hide();
    if (subWinSnapPointer->horFlip){
        subWinSnapPointer->horFlip = false;
        verFlipSnapshot->setIcon(QIcon(":/icons/false.png"));
        //tempImg = *subWinSnapPointer->img;
    //    QMatrix mat;
    //    mat = QMatrix().scale(1, -1); // make a vertical flip      !!!!!!!!!!!!!!!!!!!!!!!!1
    //    tempImg = subWinSnapPointer->img->transformed(mat);
    }
    else{
        subWinSnapPointer->horFlip = true;
        verFlipSnapshot->setIcon(QIcon(":/icons/true.png"));

    }
    QMatrix mat;
    mat = QMatrix().scale(1, -1); // make a vertical flip      !!!!!!!!!!!!!!!!!!!!!!!!1
    tempImg = subWinSnapPointer->img->transformed(mat);
    pal.setBrush(subWinSnapPointer->wgt->backgroundRole(), QBrush(tempImg));
    *subWinSnapPointer->img = tempImg;                                                                        /////
    subWinSnapPointer->wgt->setPalette(pal);
    subWinSnapPointer->wgt->resize(subWinSnapPointer->img->width(), subWinSnapPointer->img->height());
    subWinSnapPointer->wgt->show();
}

//set Horizontal Flip
void MainWindow::setFlipHor(){
    QImage tempImg;
    QPalette pal;
    subWinSnapPointer->wgt->hide();
    if (subWinSnapPointer->horFlip){
        subWinSnapPointer->horFlip = false;
        horFlipSnapshot->setIcon(QIcon(":/icons/false.png"));
   //     tempImg = *subWinSnapPointer->img;
    }
    else{
        subWinSnapPointer->horFlip = true;
        horFlipSnapshot->setIcon(QIcon(":/icons/true.png"));

    }
    QMatrix mat;
    mat = QMatrix().scale(-1, 1); // make a vertical flip      !!!!!!!!!!!!!!!!!!!!!!!!1
    tempImg = subWinSnapPointer->img->transformed(mat);
    pal.setBrush(subWinSnapPointer->wgt->backgroundRole(), QBrush(tempImg));
    *subWinSnapPointer->img = tempImg;                                                                        /////
    subWinSnapPointer->wgt->setPalette(pal);
    subWinSnapPointer->wgt->resize(subWinSnapPointer->img->width(), subWinSnapPointer->img->height());
    subWinSnapPointer->wgt->show();
}

//sending a command to current tango device without callback
void MainWindow::sendTangoCommand(Tango::DeviceProxy *device, QString command){
    try{
            device->command_inout(command.toAscii().constData());
    }
    catch(Tango::ConnectionFailed){
          fprintf(stderr, "ConnectionFailed while send tango command to %s\n", subWin->device->name().c_str());
          exit(1);
    }
    catch(Tango::WrongData){
          fprintf(stderr, "Wrong Data while send tango command to %s\n", subWin->device->name().c_str());
          exit(1);
    }
    catch(Tango::DevFailed){
         fprintf(stderr, "DevFailed while send tango command to %s", subWin->device->name().c_str());
         exit(1);
    }
}

//On Subwindow state changing
void SubWindow::handleWindowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState){
    if(newState == Qt::WindowActive){
        int i;
        fprintf(stderr,"SubWindow>>   newState == Qt::WindowActive\n");
            for (i = 0; i<parent->listSnap.size(); i++){
                 if(this == parent->listSnap.at(i)){
                    parent->curImg = i;
                    //parent->ui->lbCurWin->setText(QString("CurSnap_") + QString(i+49));
                    parent->subWinSnapPointer = this;
                    parent->setEnabledSnapshot(true);
                    parent->snapshot->setEnabled(true);
                    if (this->horFlip){
                        parent->horFlipSnapshot->setIcon(QIcon(":/icons/true.png"));
                    }
                    else{
                        parent->horFlipSnapshot->setIcon(QIcon(":/icons/false.png"));
                    }
                    break;
                }
           }
    }
    if(newState == Qt::WindowMinimized){
        fprintf(stderr,"Subwindow is minimaized\n");
        this->resize(50, 15);
    }
    if(oldState == Qt::WindowActive && isSnapshot){

    }
}

//on change size of main window
void MainWindow::resizeEvent( QResizeEvent *e ){
    QSize s = e->size();
    area->resize(s.width(), s.height()-150);   //-120 to statusTip
    ui->lbWork->move(5, s.height()-80);
    ui->lbCurWorkiningDev->move(75, s.height()-80);
    ui->statusBar->showMessage(tr("Ready"), 0);
}

//on mouse press event at picture widget
void ImageWidget::mousePressEvent ( QMouseEvent * e){
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    parent->ui->lbLastMouse->setText(QString("Last Mouse Pos: (") +
                                     QString().setNum(lastMouseX) + QString(";") + QString().setNum(lastMouseY) + QString(")") );
    fprintf(stderr, "ImageWidget::mousePressEvent\n");
}

////on mouse move event at picture widget
void ImageWidget::mouseMoveEvent ( QMouseEvent * e){
    mouseX = e->x();
    mouseY = e->y();
    parent->ui->lbCurMouse->setText(QString("Current Mouse Pos: (") +
                                    QString().setNum(mouseX) + QString(";") + QString().setNum(mouseY) + QString(")") );
    repaint();

    fprintf(stderr, "ImageWidget::mouseMoveEvent\n");
}

//on paint event
void ImageWidget::paintEvent( QPaintEvent * e){
    QPainter p(this);
    p.setPen(QPen(Qt::yellow, 2));
    p.drawLine(0, mouseY, this->width(), mouseY);
    p.drawLine(mouseX, 0, mouseX, this->height());
    fprintf(stderr, "ImageWidget::paintEvent\n");
}

//on close subwindow
void SubWindow::closeEvent ( QCloseEvent * closeEvent ){
    fprintf(stderr, "Del subWin\n");
    if (!isSnapshot){
        work = false;  //stop reading tango device       //it is not delete realtime subwindow!!!!!!OK!!!!!!!
        fprintf(stderr, "Work is %d\n", isSnapshot);
        parent->ui->btChangeDevice->setEnabled(true);
        parent->ui->btMkSnapshot->setEnabled(false);

        parent->makeSnapshot->setEnabled(false);
        parent->ui->btScaleRealTime->setEnabled(false);
        parent->setDevice->setEnabled(true);
        parent->realtime->setEnabled(false);
        parent->pushCommand->setEnabled(false);

    }
    else{
        QList<SubWindow*>::iterator iter;
        for (iter = parent->listSnap.begin(); iter < parent->listSnap.end(); ++iter){
             if(this == *iter){
                parent->subWinSnapPointer = NULL;
                fprintf(stderr,"!Delete a Snapshot!\n");
                qDeleteAll(iter, iter);                      ////current point??>>>>>
                parent->listSnap.erase(iter);
                parent->setEnabledSnapshot(false);
                break;
            }
        }
    }
}

void MainWindow::setIndex8(){
    changeColorFormat(0);
}

void MainWindow::setRGB32(){
    changeColorFormat(1);
}

void MainWindow::setARGB32(){
    changeColorFormat(2);
}

void MainWindow::setARGB32Pre(){
    changeColorFormat(3);
}
void MainWindow::setRGB16(){
    changeColorFormat(4);
}
void MainWindow::setARGB8565Pre(){
    changeColorFormat(5);
}
void MainWindow::setRGB666(){
    changeColorFormat(6);
}
void MainWindow::setARGB6666Pre(){
    changeColorFormat(7);
}
void MainWindow::setRGB555(){
    changeColorFormat(8);
}
void MainWindow::setARGB8555Pre(){
    changeColorFormat(9);
}
void MainWindow::setRGB888(){
    changeColorFormat(10);
}
void MainWindow::setRGB444(){
    changeColorFormat(11);
}
void MainWindow::setARGB4444Pre(){
    changeColorFormat(12);
}

//Change colorFormat for realtime subwin
void MainWindow::changeColorFormat(int format){
    intColorFormat = format+3;
    switch(intColorFormat){
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
        delim = 4; break;
    case QImage::Format_RGB666:
    case QImage::Format_ARGB6666_Premultiplied:
    case QImage::Format_ARGB8555_Premultiplied:
    case QImage::Format_RGB888:
    case QImage::Format_ARGB8565_Premultiplied:
        delim = 3; break;
    case QImage::Format_RGB16:
    case QImage::Format_RGB555:
    case QImage::Format_RGB444:
    case QImage::Format_ARGB4444_Premultiplied:
        delim = 2; break;
    case QImage::Format_Indexed8:
        delim = 1; break;
    }
}


void MainWindow::settingBrightnessSnapshot(){
    vSettingWin(BRIGHTNESS_SNAPSHOT);
}
void MainWindow::settingContrastSnapshot(){
    vSettingWin(CONTRAST_SNAPSHOT);
}
void MainWindow::settingGammaSnapshot(){
    vSettingWin(GAMMA_SNAPSHOT);
}
void MainWindow::settingRotationSnapshot(){
    vSettingWin(ROTATION_SNAPSHOT);
}
void MainWindow::settingScaleSnapshot(){
    vSettingWin(SCALE_SNAPSHOT);
}


void MainWindow::settingBrightnessRealtime(){
    vSettingWin(BRIGHTNESS_REALTIME);
}
void MainWindow::settingGammaRealtime(){
    vSettingWin(GAMMA_REALTIME);
}
void MainWindow::settingContrastRealtime(){
    vSettingWin(CONTRAST_REALTIME);
}
void MainWindow::settingScaleRealtime(){
    vSettingWin(SCALE_REALTIME);
}
void MainWindow::settingRotationRealtime(){
    vSettingWin(ROTATION_REALTIME);
}



void MainWindow::vSettingWin(int param){
    if (vSetting != NULL){
        fprintf(stderr, "!!!!!!!was!!!Qt::WA_DeleteOnClose !!!but !!!!!!!!!'vSetting != NULL'!!!!!!!!!!!!!!\n");
        delete vSetting;
        vSetting = NULL;

    }
    if (vSetting == NULL){
        vSetting = new VideoSettingsWin(this, param);
        vSetting->setWindowModality(Qt::ApplicationModal);
        vSetting->show();
    }
    else{
         fprintf(stderr, "!!ERROR vSetting != NULL'!!!!!!!!!!!!!!\n");
         exit(1);
    }
}

//open new device
void MainWindow::openDevInNewProc(){
    QProcess::startDetached("./TestApp",
                            QStringList() << this->tangoDev->tlServer->text()
                                << this->tangoDev->tlDevice->text()
                                << this->tangoDev->tlAttr->text(), "./");
    tangoDev->close();
    delete tangoDev;
    tangoDev = NULL;
}

void MainWindow::delVSetting(){
    delete vSetting;    ////////////////////////!!!!!!!!!!!!!!!!!!
    vSetting = NULL;
}

void MainWindow::setBrightnessValue(int val, SubWindow &subwinPointer){
        subwinPointer.wgt->hide();
        QImage tempImg;
        QPalette pal;
        tempImg = changeBrightness(*subwinPointer.img, val);
        pal.setBrush(subwinPointer.wgt->backgroundRole(), QBrush(tempImg));
        subwinPointer.wgt->setPalette(pal);
        subwinPointer.wgt->resize(subwinPointer.img->width(), subwinPointer.img->height());
        subwinPointer.wgt->show();
}

//set Brightness for snapshot
void MainWindow::changeBrightnessSnapshot(){
    bool ok = true;
    int temp;
    temp = vSetting->tl->text().toInt(&ok);
    if (ok){
        setBrightnessValue(temp, *subWinSnapPointer);
    }
    else{
        fprintf(stderr, "Check brightness value!! \n");
        exit(1);
    }
    delVSetting();
}

void MainWindow::setContrastValue(int val, SubWindow &subwinPointer){
        subwinPointer.wgt->hide();
        QImage tempImg;
        QPalette pal;
        tempImg = changeContrast(*subwinPointer.img, val);
        pal.setBrush(subwinPointer.wgt->backgroundRole(), QBrush(tempImg));
        *subwinPointer.img = tempImg;                                           /////
        subwinPointer.wgt->setPalette(pal);
        subwinPointer.wgt->resize(subwinPointer.img->width(), subwinPointer.img->height());
        subwinPointer.wgt->show();
}

//set Contrast for snapshot
void MainWindow::changeContrastSnapshot(){
    bool ok = true;
    int temp;
    temp = vSetting->tl->text().toInt(&ok);
    if (ok){
        setContrastValue(temp, *subWinSnapPointer);
    }
    else{
        fprintf(stderr, "Check brightness value!! \n");
        exit(1);
    }
    delVSetting();
}

void MainWindow::setGammaValue(int val, SubWindow &subwinPointer){
        subwinPointer.wgt->hide();
        QImage tempImg;
        QPalette pal;
        tempImg = changeGamma(*subwinPointer.img, val);
        pal.setBrush(subwinPointer.wgt->backgroundRole(), QBrush(tempImg));
        *subwinPointer.img = tempImg;                                           /////
        subwinPointer.wgt->setPalette(pal);
        subwinPointer.wgt->resize(subwinPointer.img->width(), subwinPointer.img->height());
        subwinPointer.wgt->show();
}

//set Gamma for snapshot
void MainWindow::changeGammaSnapshot(){
    bool ok = true;
    int temp;
    temp = vSetting->tl->text().toInt(&ok);
    if (ok){
        setGammaValue(temp, *subWinSnapPointer);
    }
    else{
        fprintf(stderr, "Check brightness value!! \n");
        exit(1);
    }
    delVSetting();
}

//set rotation for snapshot
void MainWindow::rotateImg(int deg){
    QTransform mat;
    bool ok = true;
    int temp;
    temp = ui->cmbRotate->itemText(deg).toInt(&ok);
    if(ok){
        mat.rotate(temp);
        subWinSnapPointer->wgt->hide();
        QImage tempImg;
        QPalette pal;

        tempImg = subWinSnapPointer->img->transformed(mat);
        *subWinSnapPointer->img = tempImg;                                           /////
        pal.setBrush(subWinSnapPointer->wgt->backgroundRole(), QBrush(tempImg));
        subWinSnapPointer->wgt->setPalette(pal);
        subWinSnapPointer->wgt->resize(tempImg.width(), tempImg.height());
        subWinSnapPointer->wgt->show();
    }
    else{
        fprintf(stderr, "Error degree rotation value !! \n");
        exit(1);
    }

}

void MainWindow::setRotateImgValue(int val, SubWindow &subwinPointer){
    QTransform mat;
    mat.rotate(val);
    subwinPointer.wgt->hide();
    QImage tempImg;
    QPalette pal;

    tempImg = subwinPointer.img->transformed(mat);

    pal.setBrush(subwinPointer.wgt->backgroundRole(), QBrush(tempImg));
    *subwinPointer.img = tempImg;                                           /////
    subwinPointer.wgt->setPalette(pal);
    subwinPointer.wgt->resize(tempImg.width(), tempImg.height());
    subwinPointer.wgt->show();
}

//set rotation for snapshot
void MainWindow::rotateImg(){
    bool ok = true;
    int temp;
    temp = vSetting->tl->text().toInt(&ok);
    if(ok){
        setRotateImgValue(temp, *subWinSnapPointer);
    }
    else{
        fprintf(stderr, "Error degree rotation value !! \n");
        exit(1);
    }
    delVSetting();
}
