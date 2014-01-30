#ifndef ETANGODEVICE_H
#define ETANGODEVICE_H
#include <tango.h>
#include <QString>
#include <QTimer>
#include <QVector>
#include <QObject>
#include <QWidget>

class TVariant
{
    QVector<unsigned short> dataSetUShortVector;
    QVector<unsigned char> dataSetUCharVector;

    QVector<unsigned short> dataReadUShortVector;
    QVector<unsigned char> dataReadUCharVector;
    bool isAttribute;
    int dataFormat;
    Tango::CmdArgType	d_type;
    Tango::AttrQuality	d_quality;
public:
    Tango::AttrQuality quality()const {return d_quality;}
    TVariant(Tango::DeviceAttribute &);
    QVector<unsigned char> toUCharVector() const;
    QVector<unsigned short> toUShortVector() const;
    bool canConvertToUCharVector() const;
    bool canConvertToUShortVector() const;
    int dimX;
    int dimY;
    bool isPicture() const;
    bool is16BitPicture() const;
};



class ImageTangoDevice : public QObject//QWidget//QObject
{
      Q_OBJECT
private:
    QString _serverName;
    QString _attrName;
    int _time;
public:
   // ~MyTangoDevice(){}
    ImageTangoDevice(){}
    ImageTangoDevice(QObject*);//(QWidget *ps);

    QTimer pingTimer;
 //   Tango::DeviceProxy* device;
    void setSource(QString, QString);
    QString source(){return _serverName+"/"+_attrName;}
    QString getServerName(){return _serverName;}
    QString getAttrName(){return _attrName;}
    void setPeriod(int);
    int period(){return 10;}// _time;}

    void getImageData(QString s );
    void checkDevice(QString s );         //Set Tango device
    bool sendCommand(QString);
    bool writeAttr(Tango::DeviceAttribute& attr);
    bool setTangoAttr(QString attrName, Tango::DeviceAttribute &attr);

    bool sendCommand(QString command, Tango::DeviceData &data);
    bool checkAttr(QString serverName, QString attrName);
public slots:
    void sendPing();
signals:
    void tangoError(QString);
    void newTangoData(const TVariant&);
};

class TDevice{

public:
    QString __serverAttrName;
    ImageTangoDevice *tango;
    TDevice(QObject *parent){ tango = new ImageTangoDevice(parent);}
   // void setPeriod(int ){}
   // int period(){return 0;}
//*
    ImageTangoDevice *device() {return tango;}
    ~TDevice(){delete tango;}

    QString _serverName;
    void setSource(QString d, QString a){_serverName = d;tango->setSource(d, a);}
    QString source(){return tango->source();}
    void setPeriod(int t) const{tango->setPeriod(t);}
    int period(){return tango->period();}
    bool sendTangoCommand(QString command){return tango->sendCommand(command);}
    QString getServerName(){return tango->getServerName();}
    QString getAttrName(){return tango->getAttrName();}
    QVector<double> getDoubleVector(QString attrName){
        Tango::DeviceAttribute* attr = new Tango::DeviceAttribute;
        vector<double> vec;
        QVector<double> vecTemp;
        //tango->setTangoAttr(attrName, *attr); //set ATTR=NULL in fail case
        if ( tango->setTangoAttr(attrName, *attr)){
            *attr>>vec;

            vecTemp.resize(attr->dim_x);
            double *uPtr = &vec[0];
            double* p = &vecTemp[0];
            for (int i=0; i<attr->dim_x; i++){
                *(p+i) = *uPtr;//vec.at(i);
                 uPtr++;
            }
            delete attr;
            return vecTemp;
        }
        else{
            delete attr;
            return QVector<double>();
        }
    }

    bool sendTangoCommand(QString command, QVector<double> value){
        Tango::DeviceData data;
        Tango::DevVarDoubleArray *in = new Tango::DevVarDoubleArray();
        in->length(value.size());
        for (int i=0; i<value.size();i++)
            (*in)[i] = value[i];
        data<<in;
        return tango->sendCommand(command,data);
    }
    bool writeAttr(QString attrName, QVector<double> value){
        Tango::DeviceAttribute* attr = new Tango::DeviceAttribute;
        if ( tango->setTangoAttr(attrName, *attr)){
            //attr << value.toStdVector();
            Tango::DevVarDoubleArray *in = new Tango::DevVarDoubleArray();
            in->length(value.size());
            for (int i=0; i<value.size();i++)
                (*in)[i] = value[i];
            *attr<<in;
            tango->writeAttr(*attr);
            return true;
        }
        delete attr;
        return false;
    }
// */
};

#endif // ETANGODEVICE_H
