#ifndef DEVICE_H
#define DEVICE_H
#include <tango.h>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QMessageBox>
#include <mydevproperty.h>
#include <QVariant>
/*!
  \file my_device.h
  \author Georgii Vasilev
  \class my_Device
  \brief Answear for dealing with Tango Device
  ///Whole connects with Tango Device
*/

class my_Device : public QObject
{
    Q_OBJECT
private:
    /*! \brief reinit property */
    void reinitProp();

    /*!
        \brief reinit property
        \param prop - property pointer
        \param param - propery name
    */
    void initNewProperty(MyDevProperty * prop, int param);

    /*!
        \brief reinstal property with new value
        \param param - property name
        \param val - value
    */
    void setNewPropertyValue(int param, QVariant val);
public:
    QTimer pingTimer;               /*!< Timer for sending ping*/
    QString attr16BitImgData;       /*!< attribute name of 16 bit data NOT USED*/
    QString attrCalcStatistic;      /*!< attribute name of calculate statistics*/
    QString attrImg;                /*!< attribute name of image*/
    QString attrStatistic;          /*!< attribute name of statistics*/
    Tango::DeviceProxy* device;     /*!< Connector with tango server*/
    QString _serverName;            /*!< Tango_Host+device_name*/
    QList <MyDevProperty *> listPropServ;   /*!< list of properties (serverside) */

    /*! \brief Constructor*/
    my_Device(QObject* parent = 0);

    /*!
        \brief init connection with tango server
        \param serv - tango_host
        \param dev - device_name
    */
    void initDevice(QString serv , QString dev);

    /*!
        \brief Try to connect with tango server (sending ping)
        \param s - tango_host + device_name
    */
    void setDevice(QString s );         //Set Tango device

    /*!
        \brief Try to get attribute value from tango server
        \param dev - tango_host + device_name
        \param attrName - attribute name
        \return tango attribute (beter do not use this function)
    */
    Tango::DeviceAttribute setTangoAttr(Tango::DeviceProxy& dev, QString attrName);

    /*!
        \brief Try to get attribute value from tango server
        \param dev - tango_host + device_name
        \param attrName - attribute name
        \param attr - Tango::DeviceAtrribute to set
        \return seccess operation
    */
    bool setTangoAttr(Tango::DeviceProxy& dev, QString attrName, Tango::DeviceAttribute &attr);

    /*!
        \brief Try to get attribute value from tango server
        \param attrName - attribute name
        \param attr - Tango::DeviceAtrribute to set
        \return seccess operation
    */
    bool setTangoAttr(int attrName, Tango::DeviceAttribute &attr);

    /*!
        \brief Try to set vector of unsigned char vector from tango attribute
        \param attrName - attribute name
        \param val - Variable to set
        \return seccess operation
    */
    bool setUCharVal(Tango::DeviceAttribute& attr, vector <unsigned char>& val);

    /*!
        \brief Try to set boolean value from tango attribute
        \param attrName - attribute name
        \param val - Variable to set
        \return seccess operation
    */
    bool setBoolVal(Tango::DeviceAttribute& attr, QString& val);

    /*!
        \brief Try to set integer value from tango attribute
        \param attrName - attribute name
        \param val - Variable to set
        \return seccess operation
    */
    bool setIntVal(Tango::DeviceAttribute& attr, int& val );

    /*!
        \brief Try to set double value from tango attribute
        \param attrName - attribute name
        \param val - Variable to set
        \return seccess operation
    */
    bool setDoubleVal(Tango::DeviceAttribute& attr, double& val);

    /*!
        \brief Try to set vector of double from tango attribute
        \param attrName - attribute name
        \param val - Variable to set
        \return seccess operation
    */
    bool setDoubleVal(Tango::DeviceAttribute& attr, vector<double>& val);

    /*!
        \brief Try to set vector of unsigned short from tango attribute
        \param attrName - attribute name
        \param val - Variable to set
        \return seccess operation
    */
    bool setUShortVal(Tango::DeviceAttribute& attr, vector <unsigned short>& val);

    /*!
        \brief Try to set boolean value from tango attribute
        \param attrName - attribute name
        \param val - Variable to set
        \return seccess operation
    */
    bool setBoolVal(Tango::DeviceAttribute& attr, bool& val);

    /*!
        \brief Set device attribute in server
        \param attr - DeviceAttribute to set
        \return seccess operation
    */
    bool writeAttr(Tango::DeviceAttribute& attr);

    /*!
        \brief Get properties frm server
        \param propName - name of property
        \param attr - DeviceAttribute to set
        \return seccess operation
    */
    bool setPropValFromServer(int propName, Tango::DeviceAttribute& attr);

    /*!
        \brief Set timer interval value
        \param val - Value (ms)
    */
    void setTimeoutVal(int val);

    /*!
        \brief read property value from server
        \param param - property name
        \return seccess operation
    */
    bool readServerPropertyVal(int param);

    /*! \brief Destructor*/
    ~my_Device();


    /*!
        \brief Check is set attribute name
        \param param - name of property
        \return seccess operation
    */
    bool propertyAttrNameIsNULL(int param);

    /*!
        \brief Check is set attribute
        \param param - name of property
        \return seccess operation
    */
    bool propertyIsNULL(int param);

    /*!
        \brief Start timer
    */
    void startWorkWithTime();
signals:
   // void setScaleDeviceVal(double val);     /*!< \brief  \param val - value*/
   // void setRotationDeviceVal(int val) ;
  //  void setContrastDeviceVal(int val) ;
  //  void setBrightnessDeviceVal(int val);
  //  void setGammaDeviceVal(int val) ;
 //   void setVerFlipDeviceVal(QString val);
 //   void setHorFlipDeviceVal(QString val);

    void sendError(QString str);        /*!< \brief on error in tango operation \param str - Error descripption*/
    void goodConnection();              /*!< \brief on good connection with tango device*/
    void correctImgAttrVal();           /*!< \brief on correct readting tango attribute*/

public slots:
    /*!
        \brief Send a command to tango device
        \param command - command for sending to tango device
        \return seccess operation
    */
    bool sendTangoCommand(QString command);

    /*!
        \brief Send a command with feedback to tango device
        \param command - command for sending to tango device
        \param devData - attribute for feedback
        \return seccess operation
    */
    bool sendTangoCommandFidBack(QString command, Tango::DeviceData& devData);

    /*!
        \brief Send a ping to tango server
    */
    void sendPing();

    /*!
        \brief Set Device attribute names
        \param lists - list of attribute names
    */
    void setAttrNames(QStringList lists );

    /*!
        \brief Set Scale value in server
        \param val - value
    */
    void setScaleDeviceValCommand(double val);

    /*!
        \brief Set Rotation value in server
        \param val - value
    */
    void setRotationDeviceValCommand(int val);

    /*!
        \brief Set Contrst value in server
        \param val - value
    */
    void setContrastDeviceValCommand(int val);

    /*!
        \brief Set Brightness value in server
        \param val - value
    */
    void setBrightnessDeviceValCommand(int val);

    /*!
        \brief Set Gamma value in server
        \param val - value
    */
    void setGammaDeviceValCommand(int val);

    /*!
        \brief Set Horizontal flip (HorFlip) value in server
        \param val - value
    */
    void setHorFlipDeviceValCommand(bool val);

    /*!
        \brief Set Vertical flip (VerFlip) value in server
        \param val - value
    */
    void setVerFlipDeviceValCommand(bool val);

    /*!
        \brief Set Horizontal flip (HorFlip) value in server
        \param val - value
    */
    void setHorFlipDeviceValCommand(QString val);

    /*!
        \brief Set Vertical flip (VerFlip) value in server
        \param val - value
    */
    void setVerFlipDeviceValCommand(QString val);
};

#endif // MY_DEVICE_H
