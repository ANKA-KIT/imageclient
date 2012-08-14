/****************************************************************************
** Meta object code from reading C++ file 'rsfl_wgt.h'
**
** Created: Tue Aug 14 09:45:55 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rsfl_wgt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rsfl_wgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RSFL_WGT[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x05,
      39,   10,    9,    9, 0x05,
      64,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      90,   10,    9,    9, 0x0a,
     108,   10,    9,    9, 0x0a,
     126,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RSFL_WGT[] = {
    "RSFL_WGT\0\0val\0sendHorFlipVal(QVariant)\0"
    "sendVerFlipVal(QVariant)\0"
    "sendRotationVal(QVariant)\0horFlipSlot(bool)\0"
    "verFlipSlot(bool)\0rotationSlot(QString)\0"
};

void RSFL_WGT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RSFL_WGT *_t = static_cast<RSFL_WGT *>(_o);
        switch (_id) {
        case 0: _t->sendHorFlipVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->sendVerFlipVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 2: _t->sendRotationVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->horFlipSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->verFlipSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->rotationSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RSFL_WGT::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RSFL_WGT::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RSFL_WGT,
      qt_meta_data_RSFL_WGT, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RSFL_WGT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RSFL_WGT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RSFL_WGT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RSFL_WGT))
        return static_cast<void*>(const_cast< RSFL_WGT*>(this));
    return QWidget::qt_metacast(_clname);
}

int RSFL_WGT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void RSFL_WGT::sendHorFlipVal(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RSFL_WGT::sendVerFlipVal(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RSFL_WGT::sendRotationVal(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
