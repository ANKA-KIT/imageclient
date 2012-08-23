#include <my_device.h>
#include <QCoreApplication>
#include <enum.h>

void my_Device::initDevice(QString serv , QString dev){
    QString serverName =      (QString)"\/\/" + serv +
                                (QString)"\/" + dev;

    setDevice(serverName);

    _serverName = serverName;
    qDebug("in my_Device initing %s", _serverName.toAscii().constData());
  if (device){
      emit goodConnection();
  }
}

my_Device::my_Device(QObject* parent)
    : QObject(parent),
      device(NULL)
{
    qDebug("in my_Device constructor!!!!");
    attrCalcStatistic = "CalculateStatistics";
    attrStatistic = "Statistics";

    MyDevProperty *br = new Brightness();
    MyDevProperty *con = new Contrast;
    MyDevProperty *gm = new Gamma();
    MyDevProperty *rot = new Rotation();
    MyDevProperty *scl = NULL;
    MyDevProperty *hfl = new HorFlip();
    MyDevProperty *vfl = new VerFlip();
//    BRIGHTNESS = 0, CONTRAST = 1, GAMMA = 2, ROTATION = 3, SCALE = 4, HOR_FLIP = 5, VER_FLIP = 6,
    listPropServ.push_back(br);
    listPropServ.push_back(con);
    listPropServ.push_back(gm);
    listPropServ.push_back(rot);
    listPropServ.push_back(scl);
    listPropServ.push_back(hfl);
    listPropServ.push_back(vfl);

    connect(&pingTimer, SIGNAL(timeout()), this, SLOT(sendPing()), Qt::DirectConnection);
    startWorkWithTime();   // puts one event in the threads event queue
    qDebug("Attention, my_Device() pingTimer STARTED");
}

my_Device::~my_Device(){
    qDebug("in my_Device deestructor!!!!!");
    pingTimer.stop();
    qDebug("Attention, in ~my_Device pingTimer STOPED");
    delete device;
    device = NULL;

    qDeleteAll(listPropServ.begin(), listPropServ.end());
}

void my_Device::sendPing(){
    qDebug("my_Device::sendPing");
    if (!device){
        qDebug("Warring, my_Device::sendPing device not inited");
        setDevice(_serverName);     //reconnection
    }
    if (device){
        try{
            int pingTime;
            qDebug("my_Device::sendPing !!!!");
            pingTime = device->ping();
            qDebug("my_Device::sendPing !!!!-Ping Time--%d", pingTime);
            emit goodConnection();
        }
        catch(const Tango::CommunicationFailed& e){
            qDebug("Error, tangoDev CommunicationFailed");
            delete device;
            device = NULL;
            emit sendError("tangoDev CommunicationFailed");
        }
        catch(const Tango::ConnectionFailed& e){
           qDebug("Error, tangoDev ConnectionFailed");
           delete device;
           device = NULL;
           emit sendError("tangoDev ConnectionFailed");
        }
        catch(const Tango::DevFailed& e){
           qDebug("Error, BIG PROBLEMS In PING!!!");
           delete device;
           device = NULL;
           emit sendError("BIG PROBLEMS In PING!!!");
        }
    }
}

void my_Device::setDevice(QString s ){
    try{
        Tango::DeviceProxy* dev;
        dev = new Tango::DeviceProxy(s.toAscii().constData());
        dev->ping();
        device = dev;
    }
    catch(const Tango::WrongNameSyntax& e){
        qDebug("Error, Wrong Name Syntax of Tango Server\n");
        delete device;
        device = NULL;
        emit sendError("Wrong Syntax");
    }
    catch(const Tango::ConnectionFailed& e){
        qDebug("Error, Connection Failed with Tango Server\n");
        //QMessageBox::information(this,"Connection Failed","Connection Failed",QMessageBox::Cancel);
        delete device;
        device = NULL;
        emit sendError("Connection Failed with Tango Server");
    }
    catch(const Tango::DevFailed& e){
            qDebug("Error, Is Failed Connection with Tango Server \n Check the name of TangoServer \n");
            delete device;
            device = NULL;
    emit sendError("Is Failed Connection with Tango Server");
    }
}

Tango::DeviceAttribute my_Device::setTangoAttr(Tango::DeviceProxy& dev, QString attrName){
    try{
        Tango::DeviceAttribute attr;

        if (&dev && attrName != ""){
            qDebug("Set Tango ATTR");
            attr = dev.read_attribute(attrName.toAscii().constData());
            if (attr.quality == Tango::ATTR_INVALID || attr.get_dim_x() == 0){
                qDebug("Error, Tango::ATTR_INVALID while reading attribute");
                emit sendError("Tango::ATTR_INVALID while reading attribute");
            }
            else{
                qDebug("Tango ATTR Set");
                emit correctImgAttrVal();
                qDebug("Signal Tango ATTR correct");
            }
        }
        return attr;
    }
    catch(const Tango::ConnectionFailed &e){
         qDebug("Error, ConnectionFailed while reading attribute");
         emit sendError("ConnectionFailed while reading attribute");
    }
    catch(const Tango::CommunicationFailed &e){
         qDebug("Error, CommunicationFailed while reading attribute");
         emit sendError("CommunicationFailed while reading attribute");
    }
    catch(const Tango::WrongData& e){
         qDebug("Error, Wrong Data while reading attribute\n");
         emit sendError("Wrong Data while reading attribute");
    }
}

bool my_Device::setTangoAttr(Tango::DeviceProxy& dev, QString attrName, Tango::DeviceAttribute &attr){
     Tango::DeviceAttribute *attribute = new Tango::DeviceAttribute();
     try{
         if (&dev  && attrName != ""){
             qDebug("Set Tango ATTR");
             *attribute = dev.read_attribute(attrName.toAscii().constData());
             if (attribute->quality == Tango::ATTR_INVALID || attribute->get_dim_x() == 0){
                 delete attribute;
                 return false;
             }
             else{
                attr = *attribute;
                delete attribute;
                return true;
             }
         }
     }
     catch(const Tango::ConnectionFailed &e){
          qDebug("Error, ConnectionFailed while reading attribute");
          emit sendError("ConnectionFailed while reading attribute");
          delete attribute;
          return false;
     }
     catch(const Tango::CommunicationFailed &e){
          qDebug("Error, CommunicationFailed while reading attribute");
          emit sendError("CommunicationFailed while reading attribute");
          delete attribute;
          return false;
     }
     catch(const Tango::WrongData& e){
          qDebug("Error, Wrong Data while reading attribute\n");
          emit sendError("Wrong Data while reading attribute");
          delete attribute;
          return false;
     }
     catch(const Tango::DevFailed& e){
          qDebug("Error, BIg problems!!!!!!\n");
          emit sendError("Wrong Data while reading attribute");
          delete attribute;
          return false;
     }

 }

bool my_Device::setTangoAttr(int propName, Tango::DeviceAttribute& attr){
    QString name;
    if (propName == IMAGE) { name = attrImg; }
    else if (propName == IMAGE_16BIT_DATA) { name = attr16BitImgData; }
    else if (propName ==  CALC_STAT){name = attrCalcStatistic; }
    else if (propName ==  STAT){name = attrStatistic;}
    else {if (!propertyIsNULL(propName)) name = listPropServ.at(propName)->getAttrName();}
    if (setTangoAttr(*device, name, attr))
        return true;
    else
        return false;
}

bool my_Device::setPropValFromServer(int propName, Tango::DeviceAttribute& attr){
    double valDb = 0.0;
    switch(propName){
        case BRIGHTNESS:
        case GAMMA:
        case CONTRAST:
            int valInt;
            if (setIntVal(attr, valInt)){
               listPropServ.at(propName)->setValue(valInt);
               return true;
             }
             else{
                 delete listPropServ[propName];
                 listPropServ[propName] = NULL;
                 return false;
             }
        break;
        case SCALE:
        case ROTATION:

            if (setDoubleVal(attr, valDb)){
              listPropServ.at(propName)->setValue(valDb);
              return true;
            }
            else{
                delete listPropServ[propName];
                listPropServ[propName] = NULL;
                return false;
            }
        break;
        case VER_FLIP:
        case HOR_FLIP:
            QString valStr;
            if (setBoolVal(attr, valStr)){
                listPropServ.at(propName)->setValue(valStr);
                return true;
            }
            else{
                delete listPropServ[propName];
                listPropServ[propName] = NULL;
                return false;
             }
        break;
    }
}


bool my_Device::setUCharVal(Tango::DeviceAttribute& attr, vector <unsigned char>& val){
    try{

        attr>>val;
        return true;
    }
    catch(Tango::DevFailed){
         qDebug("Error, Serrios error in my_Device::setUCharVal");
         return false;
    }
}

bool my_Device::setUShortVal(Tango::DeviceAttribute& attr, vector <unsigned short>& val){
    try{
        attr>>val;
        return true;
    }
    catch(Tango::DevFailed){
         qDebug("Error, Serrios error in my_Device::setUShortVal");
         return false;
    }
}
bool my_Device::setDoubleVal(Tango::DeviceAttribute& attr, double& val){
    try{
        attr>>val;
        return true;
    }
    catch(Tango::DevFailed){
         qDebug("Error, Serrios error in my_Device::setDoubleVal");
         return false;
    }
}

bool my_Device::setDoubleVal(Tango::DeviceAttribute& attr, vector<double>& val){
    try{
        attr>>val;
        return true;
    }
    catch(Tango::DevFailed){
         qDebug("Error, Serrios error in my_Device::setDoubleVal");
         return false;
    }
}

bool my_Device::setBoolVal(Tango::DeviceAttribute& attr, QString& val){
    try{
        Tango::DevLong value;
        attr>>value;
        if (value != 0){
          val = "true";
        }
        else{
          val = "false";
        }
        qDebug("Server Flip val is %d", value);
        return true;
    }
    catch(Tango::DevFailed){
         qDebug("Error, Serrios error in my_Device::setUCharVal");
         return false;
    }
}

bool my_Device::setBoolVal(Tango::DeviceAttribute& attr, bool& val){
    try{
        Tango::DevLong value;
        attr>>value;
        if (value != 0){
          val = true;
        }
        else{
          val = false;
        }
        qDebug("Server Flip val is %d", value);
        return true;
    }
    catch(Tango::DevFailed){
         qDebug("Error, Serrios error in my_Device::setUCharVal");
         return false;
    }
}

bool my_Device::setIntVal(Tango::DeviceAttribute& attr, int& val){
    try{
        Tango::DevLong valT;
        attr>>valT;
        val = valT;
        return true;
    }
    catch(Tango::DevFailed){
         qDebug("Error, Serrios error in my_Device::setIntVal");
         return false;
    }
}


bool my_Device::sendTangoCommand(QString command){
  try{
        device->command_inout(command.toAscii().constData());
        return true;
    }
    catch(const Tango::ConnectionFailed &e){
        qDebug("Error, ConnectionFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
   }
    catch(const Tango::CommunicationFailed& e){
        qDebug("Error, CommunicationFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
    catch(const Tango::DeviceUnlocked& e){
        qDebug("Error, DeviceUnlocked while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
    catch(const Tango::DevFailed& e){
        qDebug("Error, DevFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
}

void my_Device::reinitProp(){
    if (propertyIsNULL(BRIGHTNESS))
        listPropServ[BRIGHTNESS] = new Brightness();
    if (propertyIsNULL(CONTRAST))
        listPropServ[CONTRAST] = new Contrast();
    if (propertyIsNULL(GAMMA))
        listPropServ[GAMMA] = new Gamma();
    if (propertyIsNULL(ROTATION))
        listPropServ[ROTATION] = new Rotation();
    if (propertyIsNULL(HOR_FLIP))
        listPropServ[HOR_FLIP] = new HorFlip();
    if (propertyIsNULL(VER_FLIP))
        listPropServ[VER_FLIP] = new VerFlip();
}

void my_Device::setAttrNames(QStringList list ){
    reinitProp();
    listPropServ.at(BRIGHTNESS)->setAttrName(list.at(BRIGHTNESS));
    listPropServ.at(CONTRAST)->setAttrName(list.at(CONTRAST));
    listPropServ.at(GAMMA)->setAttrName(list.at(GAMMA));
    listPropServ.at(ROTATION)->setAttrName(list.at(ROTATION));
   // listPropServ.at(SCALE)->setAttrName(list.at(SCALE));   Scale not used for current version!!!!!!!!!
    listPropServ.at(HOR_FLIP)->setAttrName(list.at(HOR_FLIP));
    listPropServ.at(VER_FLIP)->setAttrName(list.at(VER_FLIP));
    attrImg = list.at(7);
    attr16BitImgData = list.at(8);

}

bool my_Device::writeAttr(Tango::DeviceAttribute& attr){
    try{
        device->write_attribute(attr);
        return true;
    }
    catch(const Tango::ConnectionFailed &e){
        qDebug("Error, ConnectionFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
   }
    catch(const Tango::CommunicationFailed& e){
        qDebug("Error, CommunicationFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
    catch(const Tango::DeviceUnlocked& e){
        qDebug("Error, DeviceUnlocked while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
    catch(const Tango::DevFailed& e){
        qDebug("Error, DevFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
}

void my_Device::initNewProperty(MyDevProperty * prop, int param){
    delete prop;
    switch(param){
        case BRIGHTNESS: prop = new Brightness(); break;
        case GAMMA: prop = new Gamma(); break;
        case CONTRAST: prop = new Contrast(); break;
        case HOR_FLIP: prop = new HorFlip(); break;
        case VER_FLIP: prop = new VerFlip(); break;
        case ROTATION: prop = new Rotation(); break;
        case SCALE: prop = new Scale(); break;
    }
}
void my_Device::setNewPropertyValue(int param, QVariant val){
    initNewProperty(listPropServ.at(param), param);
    listPropServ.at(param)->setValue(val);
}

void my_Device::setScaleDeviceValCommand(double val){
    Tango::DeviceAttribute attr;
    if(setTangoAttr(*device, listPropServ.at(SCALE)->getAttrName() , attr)){
        attr<<val;
        if (writeAttr(attr)){
            setNewPropertyValue(SCALE, val);
            qDebug("Scale value was set");
        }
        else{
            qDebug("Error, Scale value wasn't set");
        }
    }
    else{
        qDebug("Warring, Problems in initing Tango attribute");
    }
}
void my_Device::setRotationDeviceValCommand(int val){
    Tango::DeviceAttribute attr;
    if(setTangoAttr(*device, listPropServ.at(ROTATION)->getAttrName(), attr)){
        attr<<(double)val;
        if (writeAttr(attr)){
            setNewPropertyValue(ROTATION, val);
             qDebug("Rotation value was set");
        }
        else{
            qDebug("Error, Rotation value wasn't set");
        }
    }
    else{
        qDebug("Warring, Problems in initing Tango attribute");
    }
}
void my_Device::setContrastDeviceValCommand(int val){
    Tango::DeviceAttribute attr;
    if(setTangoAttr(*device, listPropServ.at(CONTRAST)->getAttrName(), attr)){
        attr<<(Tango::DevLong)val;
        if (writeAttr(attr)){
            setNewPropertyValue(CONTRAST, val);
            qDebug("Contrast value was set");
        }
        else{
            qDebug("Error, Contrast value wasn't set");
        }
    }
    else{
        qDebug("Warring, Problems in initing Tango attribute");
    }
}
void my_Device::setBrightnessDeviceValCommand(int val){
    Tango::DeviceAttribute attr;
    if(setTangoAttr(*device, listPropServ.at(BRIGHTNESS)->getAttrName(), attr)){
        attr<<(Tango::DevLong)val;
        if (writeAttr(attr)){
            setNewPropertyValue(BRIGHTNESS, val);
            qDebug("Brightness value was set");
        }
        else{
            qDebug("Error, Brightness value wasn't set");
        }
    }
    else{
        qDebug("Warring, Problems in initing Tango attribute");
    }
}
void my_Device::setGammaDeviceValCommand(int val){
    Tango::DeviceAttribute attr;
    if(setTangoAttr(*device, listPropServ.at(GAMMA)->getAttrName(), attr)){
        attr<<(Tango::DevLong)val;
        if (writeAttr(attr)){
            setNewPropertyValue(GAMMA, val);
            qDebug("Gamma value was set");
        }
        else{
            qDebug("Error, Gamma value wasn't set");
        }
    }
    else{
        qDebug("Warring, Problems in initing Tango attribute");
    }
}

void my_Device::setHorFlipDeviceValCommand(QString val){
    if (val == "true"){
        setHorFlipDeviceValCommand(true);
    }
    else{
        setHorFlipDeviceValCommand(false);
    }
}
void my_Device::setHorFlipDeviceValCommand(bool val){
    Tango::DeviceAttribute attr;
    if(setTangoAttr(*device, listPropServ.at(HOR_FLIP)->getAttrName(), attr)){
        attr<<val;
        if (writeAttr(attr)){
            setNewPropertyValue(HOR_FLIP, val);
            qDebug("HORFLIP value was set");
        }
        else{
            qDebug("Error, HORFLIP value wasn't set");
        }
    }
    else{
        qDebug("Warring, Problems in initing Tango attribute");
    }
}

void my_Device::setVerFlipDeviceValCommand(QString val){
    if (val == "true"){
        setVerFlipDeviceValCommand(true);
    }
    else{
        setVerFlipDeviceValCommand(false);
    }
}
void my_Device::setVerFlipDeviceValCommand(bool val){
    Tango::DeviceAttribute attr;
    if(setTangoAttr(*device, listPropServ.at(VER_FLIP)->getAttrName(), attr)){
        attr<<val;
        if (writeAttr(attr)){
            setNewPropertyValue(VER_FLIP, val);
            qDebug("VerFLIP value was set");
        }
        else{
            qDebug("Error, VerFLIP value wasn't set");
        }
    }
    else{
        qDebug("Warring, Problems in initing Tango attribute");
    }
}

bool my_Device::sendTangoCommandFidBack(QString command, Tango::DeviceData& devData){
  try{
        Tango::DeviceData data;
        data = device->command_inout(command.toAscii().constData());
        devData = data;
        return true;
    }
    catch(const Tango::ConnectionFailed &e){
        qDebug("Error, ConnectionFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
   }
    catch(const Tango::CommunicationFailed& e){
        qDebug("Error, CommunicationFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
    catch(const Tango::DeviceUnlocked& e){
        qDebug("Error, DeviceUnlocked while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
    catch(const Tango::DevFailed& e){
        qDebug("Error, DevFailed while write an ATTR");
        delete device;
        device = NULL;
        return false;
    }
}

bool my_Device::propertyIsNULL(int param){
    return (listPropServ.at(param) == NULL);
}

bool my_Device::propertyAttrNameIsNULL(int param){
    if (!propertyIsNULL(param))
        return listPropServ.at(param)->getAttrName().isEmpty();
    else
        return false;
}

void my_Device::startWorkWithTime(){
    setTimeoutVal(1000);
    pingTimer.start();
}

void  my_Device::setTimeoutVal(int val){
    if (val > 0)
        pingTimer.setInterval(val);
    else{
        qDebug("Set correct timeOut value, more than 0");
    }
}

bool  my_Device::readServerPropertyVal(int param){
    Tango::DeviceAttribute attr;
    if (!propertyAttrNameIsNULL(param)){
        if (setTangoAttr(param, attr)){
            if(!setPropValFromServer(param, attr)){
                  return false;
             }
        }
    }
    return true;
}
