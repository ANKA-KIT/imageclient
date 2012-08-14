#ifndef SUBWINDOWREALTIME_H
#define SUBWINDOWREALTIME_H

#include <subwindow.h>
#include <my_device.h>
#include <QCoreApplication>

#include <QHBoxLayout>


/*!
  \file subwindowrealtime.h
  \author Georgii Vasilev
  \class SubWindowRealtime
  \brief Realtime subwindow
  ///Class for dealing with tango device, displaying current picture
*/
class SubWindowRealtime : public SubWindow
{
    Q_OBJECT
private:
    // QHBoxLayout *_widgetLayout;
    bool _canBeClosed;          /*!< is the process in critical sector of geting and displaying image data*/
    QLabel *displayTime;        /*!< time of reading and displaying image data label*/
    QLabel *set1;               /*!< 1 tango device setting*/
    QLabel *set2;               /*!< 2 tango device setting*/
    QLabel *set3;               /*!< 3 tango device setting*/
    QLabel *set4;               /*!< 4 tango device setting*/
    QLabel *set5;               /*!< 5 tango device setting*/

    /*!
      \brief Set value of numeric property
      \param param - property number
      \param val - property value
    */
    void setLocalNumericVal(int param, double val);

    /*!
      \brief get rotation value
    */
    double getDegree();

    /*!
      \brief Set correct property value which depends from server side value
      \param param - property number
      \param dif - property different between values
    */
    void setLocalPropertyValOnServerDifVal(int param, double dif);

    /*!
      \brief Set server side value
      \param param - property number
      \return is it posible to read and set serverside value
    */
    bool readServerPropertyVal(int param);

    /*!
      \brief SetClientSide value eqval serverside
      \param param - property number
    */
    void chConnectsClient(int param);

    /*!
      \brief Set labels with static tango server information
      \param lb - labrl pointer
      \param val - tango server  information Value
      \param iter - number of static  tango server information
    */
    void setStat(QLabel *lb, double val, int iter);

    /*!
      \brief On getting new image from tango server (Full picture mode)
      \param x - width of subwindow
      \param y - height of subwindow
    */
    void fullPictureModeResize(int x, int y);

    /*!
      \brief On getting new image from tango server (Siziable picture more)
      \param x - width of subwindow
      \param y - height of subwindow
    */
    void scaledPictureModeResize(int x, int y);

    /*!
      \brief Set value of numeric property in client side
      \param param - property number
      \param val - property value
    */
    void setClientSideNumericVal(int param, double val);

    /*!
      \brief Set Connects client side properties with labels
    */
    void setClientSideConnects();

    /*!
      \brief Set disconnects client side properties with labels
    */
    void setClientSideDisconnects();

    /*!
      \brief Set Connects server side properties with labels
    */
    void setServerSideConnects();

    /*!
      \brief Init time label
    */
    void initTimeLb();

    /*!
      \brief Init full picture mode
    */
    void initFullPicMode();

    /*!
      \brief Init siziable mode
    */
    void initSizableMode();

    /*!
      \brief Init tango device object
    */
    void initMyDev(QString serv, QString attr);

    /*!
      \brief set static tango server values
    */
    void setStatVal(vector<double>);

    /*!
      \brief read image properties from server
    */
    void serverSide();

    /*!
      \brief make image from server
    */
    bool makeImg();
public:
    my_Device *myDev;           /*!< Tango device class pointer*/
    QString _server;            /*!< server name (HOST:DEVICE)*/
    QString _imgAttr;           /*!< attr - image attribute name*/
    bool serverOperation;       /*!< is server operation*/
    bool work;                  /*!< is the process was in subwindow close event*/
    bool pause;                 /*!< is it all ok with tango connection*/
    bool isTimeout;             /*!< is user set delay*/
    bool isResized;             /*!< is widget resized*/
    double *difLevelPers;       /*!< this is value width/height of widget*/

    /*!
        \brief Constructor
        \param serv - server name (HOST:DEVICE)
        \param attr - image attribute name
    */
    SubWindowRealtime(QString serv, QString attr);

    /*!
        \brief set pause value
        \param p - value to set pause
    */
    void setPause(bool p);

    /*!
        \brief is realtime subwindow can be close
        \return _canBeClosed value
    */
    bool isCanBeClosed();

    /*!
        \brief Destructor
    */
    ~SubWindowRealtime();
signals:
    void closeRealtime(SubWindowRealtime*);        /*!< realtime subwindow was closed \param pointer - subwindow pointer*/
    void realtimeWinChanged(SubWindowRealtime*); /*!< realtime subwindow state was changed \param pointer - subwindow pointer*/
    void isUShortData();                         /*!< inform about unsigned short data in image data of tangoserver*/
    void isUCharData();                        /*!< inform about unsigned char data in image data of tangoserver*/
    void ping();                              /*!< sending ping to tango device*/

public slots:
    /*!
        \brief Set default values
    */
    void resetImg();

    /*!
        \brief Set default values
    */
    void resetServerParam();

    /*!
        \brief resize subwindow
        \param x - width
        \param y - height
    */
    void resizeWgt(int x, int y);

    /*!
        \brief on click close
        \param e - event pointer
    */
    void closeEvent ( QCloseEvent * e);

    /*!
        \brief on window state change
        \param oldWSt - last window station
        \param newWSt - new window station
    */
    void handleWindowStateChanged(Qt::WindowStates oldWSt, Qt::WindowStates newWSt);

    /*!
        \brief on tango device error
        \param str - message error
    */
    void testOnError(QString str);

    /*!
        \brief on tango device good connection
    */
    void testOnOk();

    /*!
        \brief on needing to get new image from server
    */
    void sendingPing();

    /*!
        \brief change scale value on some value
        \param val - value
    */
    void chScaleOn(double val);

    /*!
        \brief change rotation value on some value
        \param val - value
    */
    void chRotationOn(double val);

    /*!
        \brief change brightness value on some value
        \param val - value
    */
    void chBrightnessOn(int val);

    /*!
        \brief change gamma value on some value
        \param val - value
    */
    void chGammaOn(int val);

    /*!
        \brief change contrast value on some value
        \param val - value
    */
    void chContrastOn(int val);

    /*!
        \brief set scale value server/client
        \param val - value
    */
    void setScale(double val);

    /*!
        \brief set rotation value server/client
        \param val - value
    */
    void setRotation(double val);

    /*!
        \brief set brightness value server/client
        \param val - value
    */
    void setBrightness(int val);

    /*!
        \brief set gamma value server/client
        \param val - value
    */
    void setGamma(int val);

    /*!
        \brief set contrast value server/client
        \param val - value
    */
    void setContrast(int val);

    /*!
        \brief set horizontal fliping value server/client
        \param val - value
    */
    void setHorFlipValue(QString val);

    /*!
        \brief set vertical fliping value server/client
        \param val - value
    */
    void setVerFlipValue(QString val);

    /*!
        \brief set server/client side
    */
    void chServerOperation();

    /*!
        \brief send a command to tango server
        \param com - command to server
    */
    void sendTangoCommand(QString com);

    /*!
        \brief set image mode
    */
    void setImageMode(int mode);

    /*!
        \brief read-set static tango server values
    */
    void calcStat();

    /*!
        \brief set timeout value for reading getting image from tango server
        \param val - value (ms)
    */
    void setTimeOutVal(int val);

    /*!
        \brief set timeout
        \param p - value
    */
    void setTimeOut(bool p);

    /*!
        \brief set/unset fullpicture mode
        \param val - set/unset fullPictureMode (true - set fullPictureMode/ false - set siziable mode)
    */
    void setFullPictureMode(bool val);

    /*!
        \brief on resize widget
        \param event - event pointer
    */
    void resizeEvent ( QResizeEvent * event ) ;
};

#endif // SUBWINDOWREALTIME_H
