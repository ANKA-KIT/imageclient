/****************************************************************************
** Meta object code from reading C++ file 'my_device.h'
**
** Created: Tue Aug 14 09:45:30 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "my_device.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_device.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_my_Device[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   11,   10,   10, 0x05,
      34,   10,   10,   10, 0x05,
      51,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   76,   71,   10, 0x0a,
     126,  110,   71,   10, 0x0a,
     178,   10,   10,   10, 0x0a,
     195,  189,   10,   10, 0x0a,
     225,  221,   10,   10, 0x0a,
     258,  221,   10,   10, 0x0a,
     291,  221,   10,   10, 0x0a,
     324,  221,   10,   10, 0x0a,
     359,  221,   10,   10, 0x0a,
     389,  221,   10,   10, 0x0a,
     422,  221,   10,   10, 0x0a,
     455,  221,   10,   10, 0x0a,
     491,  221,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_my_Device[] = {
    "my_Device\0\0str\0sendError(QString)\0"
    "goodConnection()\0correctImgAttrVal()\0"
    "bool\0command\0sendTangoCommand(QString)\0"
    "command,devData\0"
    "sendTangoCommandFidBack(QString,Tango::DeviceData&)\0"
    "sendPing()\0lists\0setAttrNames(QStringList)\0"
    "val\0setScaleDeviceValCommand(double)\0"
    "setRotationDeviceValCommand(int)\0"
    "setContrastDeviceValCommand(int)\0"
    "setBrightnessDeviceValCommand(int)\0"
    "setGammaDeviceValCommand(int)\0"
    "setHorFlipDeviceValCommand(bool)\0"
    "setVerFlipDeviceValCommand(bool)\0"
    "setHorFlipDeviceValCommand(QString)\0"
    "setVerFlipDeviceValCommand(QString)\0"
};

void my_Device::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        my_Device *_t = static_cast<my_Device *>(_o);
        switch (_id) {
        case 0: _t->sendError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->goodConnection(); break;
        case 2: _t->correctImgAttrVal(); break;
        case 3: { bool _r = _t->sendTangoCommand((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->sendTangoCommandFidBack((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< Tango::DeviceData(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->sendPing(); break;
        case 6: _t->setAttrNames((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: _t->setScaleDeviceValCommand((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setRotationDeviceValCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setContrastDeviceValCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setBrightnessDeviceValCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setGammaDeviceValCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setHorFlipDeviceValCommand((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->setVerFlipDeviceValCommand((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->setHorFlipDeviceValCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->setVerFlipDeviceValCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData my_Device::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject my_Device::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_my_Device,
      qt_meta_data_my_Device, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &my_Device::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *my_Device::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *my_Device::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_my_Device))
        return static_cast<void*>(const_cast< my_Device*>(this));
    return QObject::qt_metacast(_clname);
}

int my_Device::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void my_Device::sendError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void my_Device::goodConnection()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void my_Device::correctImgAttrVal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
