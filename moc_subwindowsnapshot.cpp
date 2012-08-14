/****************************************************************************
** Meta object code from reading C++ file 'subwindowsnapshot.h'
**
** Created: Tue Aug 14 09:45:44 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "subwindowsnapshot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'subwindowsnapshot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SubWindowSnapshot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   19,   18,   18, 0x05,
      66,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      98,   96,   18,   18, 0x0a,
     137,  123,   18,   18, 0x0a,
     201,  197,   18,   18, 0x0a,
     219,  197,   18,   18, 0x0a,
     240,  197,   18,   18, 0x0a,
     260,  197,   18,   18, 0x0a,
     275,  197,   18,   18, 0x0a,
     293,   18,   18,   18, 0x0a,
     308,  304,   18,   18, 0x0a,
     327,  197,   18,   18, 0x0a,
     344,  197,   18,   18, 0x0a,
     364,  197,   18,   18, 0x0a,
     383,  197,   18,   18, 0x0a,
     397,  197,   18,   18, 0x0a,
     414,  197,   18,   18, 0x0a,
     439,  197,   18,   18, 0x0a,
     469,  464,   18,   18, 0x0a,
     493,  487,   18,   18, 0x0a,
     520,  197,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SubWindowSnapshot[] = {
    "SubWindowSnapshot\0\0pointer\0"
    "SnapshotWinChanged(SubWindowSnapshot*)\0"
    "closeSnap(SubWindowSnapshot*)\0e\0"
    "closeEvent(QCloseEvent*)\0oldWSt,newWSt\0"
    "handleWindowStateChanged(Qt::WindowStates,Qt::WindowStates)\0"
    "val\0chScaleOn(double)\0chRotationOn(double)\0"
    "chBrightnessOn(int)\0chGammaOn(int)\0"
    "chContrastOn(int)\0resetImg()\0x,y\0"
    "resizeWgt(int,int)\0setScale(double)\0"
    "setRotation(double)\0setBrightness(int)\0"
    "setGamma(int)\0setContrast(int)\0"
    "setHorFlipValue(QString)\0"
    "setVerFlipValue(QString)\0mode\0"
    "setImageMode(int)\0event\0"
    "resizeEvent(QResizeEvent*)\0"
    "setFullPictureMode(bool)\0"
};

void SubWindowSnapshot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SubWindowSnapshot *_t = static_cast<SubWindowSnapshot *>(_o);
        switch (_id) {
        case 0: _t->SnapshotWinChanged((*reinterpret_cast< SubWindowSnapshot*(*)>(_a[1]))); break;
        case 1: _t->closeSnap((*reinterpret_cast< SubWindowSnapshot*(*)>(_a[1]))); break;
        case 2: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 3: _t->handleWindowStateChanged((*reinterpret_cast< Qt::WindowStates(*)>(_a[1])),(*reinterpret_cast< Qt::WindowStates(*)>(_a[2]))); break;
        case 4: _t->chScaleOn((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->chRotationOn((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->chBrightnessOn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->chGammaOn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->chContrastOn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->resetImg(); break;
        case 10: _t->resizeWgt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->setScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setRotation((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setBrightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->setGamma((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->setContrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->setHorFlipValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->setVerFlipValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->setImageMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 20: _t->setFullPictureMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SubWindowSnapshot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SubWindowSnapshot::staticMetaObject = {
    { &SubWindow::staticMetaObject, qt_meta_stringdata_SubWindowSnapshot,
      qt_meta_data_SubWindowSnapshot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SubWindowSnapshot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SubWindowSnapshot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SubWindowSnapshot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SubWindowSnapshot))
        return static_cast<void*>(const_cast< SubWindowSnapshot*>(this));
    return SubWindow::qt_metacast(_clname);
}

int SubWindowSnapshot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SubWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void SubWindowSnapshot::SnapshotWinChanged(SubWindowSnapshot * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SubWindowSnapshot::closeSnap(SubWindowSnapshot * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
