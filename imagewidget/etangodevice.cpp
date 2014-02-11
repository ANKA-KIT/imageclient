#include "etangodevice.h"

TVariant::TVariant(Tango::DeviceAttribute &attr){
    isAttribute = true;
    dataFormat = attr.get_data_format();

    if (attr.is_empty())
    {
        //qDebug() << QThread::currentThread() << ":" << this << "setDeviceAttribute() - device attribute is empty";
       // setMessage("device attribute is empty");
        d_quality = Tango::ATTR_INVALID;
        return;
    }
    /* attribute data type, if attribute is not empty */
    d_type = (Tango::CmdArgType) attr.get_type();

    if (attr.has_failed())
    {
        //qDebug() << QThread::currentThread() << ":" << this << "setDeviceAttribute() - read_attribute has failed";
       // setMessage(attr.get_err_stack());
        d_quality = Tango::ATTR_INVALID;
        return;
    }
 try {
   // if (dataFormat == Tango::IMAGE){
       // vec.clear();

        dimX = attr.get_dim_x();
        dimY = attr.get_dim_y();
       // if (d_type != DEV_UCHAR){  ///DEV_USHORT
        if (d_type == Tango::DEV_USHORT){  ///DEV_USHORT

           dataReadUShortVector.clear();
            vector<unsigned short> tempVector16;
            attr >> tempVector16;
            int count = tempVector16.size();
            unsigned short *ushortPtr = &tempVector16[0];
            dataReadUShortVector.resize(count);
            unsigned short * ptrData = &dataReadUShortVector[0];

            for(int i=0; i<count; i++){
               *ptrData = *(ushortPtr+i); ptrData++;}

        //    attr >> tempVector16;//dataReadUShortVector;
            return;
        }
        if (d_type == Tango::DEV_UCHAR){
            dataReadUCharVector.clear();
           vector<unsigned char> tempVector;
           tempVector.resize(dimX*dimY);
            attr >> tempVector;
            int count = tempVector.size();
            dataReadUCharVector.resize(count);
            unsigned char * ptrData = &dataReadUCharVector[0];
            unsigned char *ucharPtr = &tempVector[0];
            for(int i=0; i<count; i++){
                *ptrData = *(ucharPtr+i); ptrData++;}

         //   attr >> dataReadUCharVector;
            return;
   //     }
    }
} catch (Tango::DevFailed &e) {
    //setMessage(e.errors);
    d_quality = Tango::ATTR_INVALID;
}
}

QVector<unsigned char> TVariant::toUCharVector() const{
    return dataReadUCharVector;
}
QVector<unsigned short> TVariant::toUShortVector() const{
    return dataReadUShortVector;
}
bool TVariant::isPicture() const{
    if( !canConvertToUCharVector())
        return false;
    if (dataReadUCharVector.size() == 0)
        return false;
    else
        return true;
}
bool TVariant::is16BitPicture() const{
    if(!canConvertToUShortVector())
        return false;
    if (dataReadUShortVector.size() == 0)
        return false;
    else
        return true;
}

bool TVariant::canConvertToUCharVector() const{
    if(isAttribute &&  dataFormat != Tango::IMAGE)
        return false;

    switch (d_type)
    {
    case Tango::DEV_UCHAR:
        return true;
    default:
        return false;
    }
}
bool TVariant::canConvertToUShortVector() const{
    if(isAttribute &&  dataFormat != Tango::IMAGE)
        return false;

    switch (d_type)
    {
    case Tango::DEV_USHORT:
        return true;
    default:
        return false;
    }
}

void ImageTangoDevice::setSource(QString val, QString valA){
    _serverName = val;
    _attrName = valA;
}

void ImageTangoDevice::setPeriod(int val){
    if (val > 1)
        _time = val;
    else{
        _time = 2;
    }
    pingTimer.setInterval(_time);
}



//ETangoDevice::ETangoDevice(QObject *parent):  QObject(parent)

void ImageTangoDevice::sendPing(){
    getImageData(_serverName);
}

void ImageTangoDevice::checkDevice(QString s ){
    try{
        Tango::DeviceProxy dev(("//"+s).toAscii().constData());
    }
    catch(const Tango::WrongNameSyntax& e){
        qDebug("Error, Wrong Name Syntax of Tango Server\n");
        emit tangoError(QString("Wrong Syntax"));
    }
    catch(const Tango::ConnectionFailed& e){
        qDebug("Error, Connection Failed with Tango Server\n");
        emit tangoError("Connection Failed with Tango Server");
    }
    catch(const Tango::DevFailed& e){
            qDebug("Error, Is Failed Connection with Tango Server \n Check the name of TangoServer \n");
        emit tangoError("Is Failed Connection with Tango Server");
    }
}



void ImageTangoDevice::getImageData(QString s ){
    try{
        Tango::DeviceProxy dev(s.toAscii().constData());
        Tango::DeviceAttribute attr = dev.read_attribute(_attrName.toAscii().constData());
        TVariant v(attr);
        emit newTangoData(v);
    }
    catch(const Tango::WrongNameSyntax& e){
        qDebug("Error, Wrong Name Syntax of Tango Server\n");
        emit tangoError(QString("Wrong Syntax"));
    }
    catch(const Tango::ConnectionFailed& e){
        qDebug("Error, Connection Failed with Tango Server\n");
        emit tangoError("Connection Failed with Tango Server");
    }
    catch(const Tango::DevFailed& e){
            qDebug("Error, Is Failed Connection with Tango Server \n Check the name of TangoServer \n");
        emit tangoError("Is Failed Connection with Tango Server");
    }
}


ImageTangoDevice::ImageTangoDevice(QObject* p): QObject(p)//(QWidget *ps): QWidget(ps)
{
    _serverName = "";
    setPeriod(1000);
     connect(&pingTimer, SIGNAL(timeout()), this, SLOT(sendPing()), Qt::DirectConnection);
    pingTimer.start();
}

bool ImageTangoDevice::sendCommand(QString command){
try{
      Tango::DeviceProxy dev(("//"+_serverName).toAscii().constData());
      dev.command_inout(command.toAscii().constData());
      return true;
  }
  catch(const Tango::ConnectionFailed &e){
      qDebug("Error, ConnectionFailed while Send a command to server");
      fprintf(stderr, "ConnectionFailed while Send a command to server");
      Tango::Except::print_exception(e);
      return false;
 }
  catch(const Tango::CommunicationFailed& e){
      qDebug("Error, CommunicationFailed while Send a command to server");
      fprintf(stderr, "CommunicationFailed while Send a command to server");
      Tango::Except::print_exception(e);
      return false;
  }
  catch(const Tango::DeviceUnlocked& e){
      qDebug("Error, DeviceUnlocked while Send a command to server");
      fprintf(stderr, "DeviceUnlocked while Send a command to server");
      Tango::Except::print_exception(e);
      return false;
  }
  catch(const Tango::DevFailed& e){
      qDebug("Error, DevFailed while Send a command to server");
      fprintf(stderr, "DevFailed while Send a command to server");
      Tango::Except::print_exception(e);
      return false;
  }
}

bool ImageTangoDevice::sendCommand(QString command, Tango::DeviceData &data){
try{
      Tango::DeviceProxy dev(("//"+_serverName).toAscii().constData());
      //dev.command_inout(command.toAscii().constData());
      dev.command_inout(command.toAscii().constData(), data);
      return true;
  }
  catch(const Tango::ConnectionFailed &e){
      qDebug("Error, ConnectionFailed while Send a command to server");
      fprintf(stderr, "ConnectionFailed while Send a command to server");
      Tango::Except::print_exception(e);
      return false;
 }
  catch(const Tango::CommunicationFailed& e){
      qDebug("Error, CommunicationFailed while Send a command to server");
      fprintf(stderr, "CommunicationFailed while Send a command to server");
      Tango::Except::print_exception(e);
      return false;
  }
  catch(const Tango::DeviceUnlocked& e){
      qDebug("Error, DeviceUnlocked while Send a command to server");
      fprintf(stderr, "DeviceUnlocked while Send a command to server");
      Tango::Except::print_exception(e);
      return false;
  }
  catch(const Tango::DevFailed& e){
      qDebug("Error, DevFailed while Send a command to server");
      fprintf(stderr, "DevFailed while Send a command to server");
      Tango::Except::print_exception(e);
      return false;
  }
}

bool ImageTangoDevice::readBoolAttr(QString name) const
{
    Tango::DeviceProxy dev(("//" + _serverName).toAscii().constData());
    Tango::DeviceAttribute attr = dev.read_attribute(name.toAscii().constData());
    bool result;
    attr >> result;
    return result;
}

uint ImageTangoDevice::readULongAttr(QString name) const
{
    Tango::DeviceProxy dev(("//" + _serverName).toAscii().constData());
    Tango::DeviceAttribute attr = dev.read_attribute(name.toAscii().constData());
    Tango::DevULong result;
    attr >> result;
    return static_cast<uint>(result);
}

std::vector<uint> ImageTangoDevice::readULongSpectrumAttr(QString name) const
{
    Tango::DeviceProxy dev(("//" + _serverName).toAscii().constData());
    Tango::DeviceAttribute attr = dev.read_attribute(name.toAscii().constData());
    vector<Tango::DevULong> tangoResult;
    attr >> tangoResult;
    // HACK: somehow our result is longer than the x dimension, so trim it!
    tangoResult.resize(attr.get_dim_x());
    vector<uint> result(tangoResult.begin(), tangoResult.end());
    return result;
}

std::vector<uchar> ImageTangoDevice::readUCharSpectrumAttr(QString name) const
{
    Tango::DeviceProxy dev(("//" + _serverName).toAscii().constData());
    Tango::DeviceAttribute attr = dev.read_attribute(name.toAscii().constData());
    vector<uchar> result;
    attr >> result;
    // HACK: somehow our result is longer than the x dimension, so trim it!
    result.resize(attr.get_dim_x());
    return result;
}

bool ImageTangoDevice::writeAttr(Tango::DeviceAttribute& attr){
    try{
        Tango::DeviceProxy dev(("//" + _serverName).toAscii().constData());
        dev.write_attribute(attr);
        return true;
    }
    catch(const Tango::ConnectionFailed &e){
        qDebug("Error, ConnectionFailed while write an ATTR");
        fprintf(stderr,"ConnectionFailed while write an ATTR");
        Tango::Except::print_exception(e);
        return false;
   }
    catch(const Tango::CommunicationFailed& e){
        qDebug("Error, CommunicationFailed while write an ATTR");
        fprintf(stderr,"CommunicationFailed while write an ATTR");
        Tango::Except::print_exception(e);
        return false;
    }
    catch(const Tango::DeviceUnlocked &e){
        qDebug("Error, DeviceUnlocked while write an ATTR");
        fprintf(stderr,"DeviceUnlocked while write an ATTR");
        Tango::Except::print_exception(e);
        return false;
    }
    catch(const Tango::DevFailed &e){
        qDebug("Error, DevFailed while write an ATTR");
        fprintf(stderr,"DevFailed while write an ATTR");
        Tango::Except::print_exception(e);
        return false;
    }
}

bool ImageTangoDevice::setTangoAttr(QString attrName, Tango::DeviceAttribute& attr){
    try{
        Tango::DeviceProxy dev(("//"+_serverName).toAscii().constData());
        attr = dev.read_attribute(attrName.toAscii().constData());
        if (attr.quality == Tango::ATTR_INVALID || attr.get_dim_x() == 0){
            //delete attr;
            //attr = NULL;
            return false;
        }
    }
    catch(const Tango::ConnectionFailed &e){
         qDebug("Error, ConnectionFailed while reading attribute");
         emit tangoError("ConnectionFailed while reading attribute");
        // delete attr;
        // attr = NULL;
return false;
    }
    catch(const Tango::CommunicationFailed &e){
         qDebug("Error, CommunicationFailed while reading attribute");
         emit tangoError("CommunicationFailed while reading attribute");
         //delete attr;
         //attr = NULL;
return false;
    }
    catch(const Tango::WrongData& e){
         qDebug("Error, Wrong Data while reading attribute\n");
         emit tangoError("Wrong Data while reading attribute");
    //     delete attr;
     //    attr = NULL;
    }
    catch(const Tango::DevFailed& e){
         qDebug("Error, BIg problems!!!!!!\n");
         emit tangoError("Wrong Data while reading attribute");
       //  delete attr;
         //attr = NULL;
         return false;
    }
    return true;
}


bool ImageTangoDevice::checkAttr(QString serverName, QString attrName){
    try{
        Tango::DeviceProxy dev(("//"+serverName).toAscii().constData());
        Tango::DeviceAttribute attr;
        attr = dev.read_attribute(attrName.toAscii().constData());
        if (attr.quality == Tango::ATTR_INVALID || attr.get_dim_x() == 0){
            return false;
        }
        else{
           return true;
        }
    }
    catch(const Tango::ConnectionFailed &e){
         qDebug("Error, ConnectionFailed while reading attribute");
         emit tangoError("ConnectionFailed while reading attribute");
        return false;
    }
    catch(const Tango::CommunicationFailed &e){
         qDebug("Error, CommunicationFailed while reading attribute");
         emit tangoError("CommunicationFailed while reading attribute");
        return false;
    }
    catch(const Tango::WrongData& e){
         qDebug("Error, Wrong Data while reading attribute\n");
         emit tangoError("Wrong Data while reading attribute");
         return false;
    }
    catch(const Tango::DevFailed& e){
         qDebug("Error, BIg problems!!!!!!\n");
         emit tangoError("Wrong Data while reading attribute");
         return false;
    }
}
