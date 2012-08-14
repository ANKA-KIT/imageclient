/****************************************************************************
** Meta object code from reading C++ file 'starttangowin.h'
**
** Created: Tue Aug 14 09:45:33 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "starttangowin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'starttangowin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StartTangoWin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,
      45,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   14,   14,   14, 0x0a,
      61,   14,   14,   14, 0x0a,
      72,   14,   14,   14, 0x0a,
      93,   14,   14,   14, 0x0a,
     104,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StartTangoWin[] = {
    "StartTangoWin\0\0,\0correctDev(QString,QString)\0"
    "cancel()\0onOk()\0onCancel()\0"
    "testOnError(QString)\0testOnOk()\0"
    "testOnOkImgVal()\0"
};

void StartTangoWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StartTangoWin *_t = static_cast<StartTangoWin *>(_o);
        switch (_id) {
        case 0: _t->correctDev((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->cancel(); break;
        case 2: _t->onOk(); break;
        case 3: _t->onCancel(); break;
        case 4: _t->testOnError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->testOnOk(); break;
        case 6: _t->testOnOkImgVal(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StartTangoWin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StartTangoWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StartTangoWin,
      qt_meta_data_StartTangoWin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StartTangoWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StartTangoWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StartTangoWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StartTangoWin))
        return static_cast<void*>(const_cast< StartTangoWin*>(this));
    return QWidget::qt_metacast(_clname);
}

int StartTangoWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void StartTangoWin::correctDev(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StartTangoWin::cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
