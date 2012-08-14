/****************************************************************************
** Meta object code from reading C++ file 'subwindowrealtime.h'
**
** Created: Tue Aug 14 09:45:38 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "subwindowrealtime.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'subwindowrealtime.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SubWindowRealtime[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      53,   18,   18,   18, 0x05,
      92,   18,   18,   18, 0x05,
     107,   18,   18,   18, 0x05,
     121,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     128,   18,   18,   18, 0x0a,
     139,   18,   18,   18, 0x0a,
     162,  158,   18,   18, 0x0a,
     183,  181,   18,   18, 0x0a,
     222,  208,   18,   18, 0x0a,
     286,  282,   18,   18, 0x0a,
     307,   18,   18,   18, 0x0a,
     318,   18,   18,   18, 0x0a,
     336,  332,   18,   18, 0x0a,
     354,  332,   18,   18, 0x0a,
     375,  332,   18,   18, 0x0a,
     395,  332,   18,   18, 0x0a,
     410,  332,   18,   18, 0x0a,
     428,  332,   18,   18, 0x0a,
     445,  332,   18,   18, 0x0a,
     465,  332,   18,   18, 0x0a,
     484,  332,   18,   18, 0x0a,
     498,  332,   18,   18, 0x0a,
     515,  332,   18,   18, 0x0a,
     540,  332,   18,   18, 0x0a,
     565,   18,   18,   18, 0x0a,
     589,  585,   18,   18, 0x0a,
     620,  615,   18,   18, 0x0a,
     638,   18,   18,   18, 0x0a,
     649,  332,   18,   18, 0x0a,
     670,  668,   18,   18, 0x0a,
     687,  332,   18,   18, 0x0a,
     718,  712,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SubWindowRealtime[] = {
    "SubWindowRealtime\0\0closeRealtime(SubWindowRealtime*)\0"
    "realtimeWinChanged(SubWindowRealtime*)\0"
    "isUShortData()\0isUCharData()\0ping()\0"
    "resetImg()\0resetServerParam()\0x,y\0"
    "resizeWgt(int,int)\0e\0closeEvent(QCloseEvent*)\0"
    "oldWSt,newWSt\0"
    "handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates)\0"
    "str\0testOnError(QString)\0testOnOk()\0"
    "sendingPing()\0val\0chScaleOn(double)\0"
    "chRotationOn(double)\0chBrightnessOn(int)\0"
    "chGammaOn(int)\0chContrastOn(int)\0"
    "setScale(double)\0setRotation(double)\0"
    "setBrightness(int)\0setGamma(int)\0"
    "setContrast(int)\0setHorFlipValue(QString)\0"
    "setVerFlipValue(QString)\0chServerOperation()\0"
    "com\0sendTangoCommand(QString)\0mode\0"
    "setImageMode(int)\0calcStat()\0"
    "setTimeOutVal(int)\0p\0setTimeOut(bool)\0"
    "setFullPictureMode(bool)\0event\0"
    "resizeEvent(QResizeEvent*)\0"
};

void SubWindowRealtime::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SubWindowRealtime *_t = static_cast<SubWindowRealtime *>(_o);
        switch (_id) {
        case 0: _t->closeRealtime((*reinterpret_cast< SubWindowRealtime*(*)>(_a[1]))); break;
        case 1: _t->realtimeWinChanged((*reinterpret_cast< SubWindowRealtime*(*)>(_a[1]))); break;
        case 2: _t->isUShortData(); break;
        case 3: _t->isUCharData(); break;
        case 4: _t->ping(); break;
        case 5: _t->resetImg(); break;
        case 6: _t->resetServerParam(); break;
        case 7: _t->resizeWgt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 9: _t->handleWindowStateChanged((*reinterpret_cast< Qt::WindowStates(*)>(_a[1])),(*reinterpret_cast< Qt::WindowStates(*)>(_a[2]))); break;
        case 10: _t->testOnError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->testOnOk(); break;
        case 12: _t->sendingPing(); break;
        case 13: _t->chScaleOn((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->chRotationOn((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->chBrightnessOn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->chGammaOn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->chContrastOn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->setScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->setRotation((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->setBrightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->setGamma((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->setContrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->setHorFlipValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->setVerFlipValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->chServerOperation(); break;
        case 26: _t->sendTangoCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->setImageMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->calcStat(); break;
        case 29: _t->setTimeOutVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->setTimeOut((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->setFullPictureMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SubWindowRealtime::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SubWindowRealtime::staticMetaObject = {
    { &SubWindow::staticMetaObject, qt_meta_stringdata_SubWindowRealtime,
      qt_meta_data_SubWindowRealtime, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SubWindowRealtime::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SubWindowRealtime::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SubWindowRealtime::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SubWindowRealtime))
        return static_cast<void*>(const_cast< SubWindowRealtime*>(this));
    return SubWindow::qt_metacast(_clname);
}

int SubWindowRealtime::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SubWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void SubWindowRealtime::closeRealtime(SubWindowRealtime * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SubWindowRealtime::realtimeWinChanged(SubWindowRealtime * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SubWindowRealtime::isUShortData()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SubWindowRealtime::isUCharData()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SubWindowRealtime::ping()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
