/****************************************************************************
** Meta object code from reading C++ file 'tangosettingswin.h'
**
** Created: Tue Aug 14 09:45:48 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tangosettingswin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tangosettingswin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TangoSettingsWin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   18,   17,   17, 0x05,
      51,   17,   17,   17, 0x05,
      72,   17,   17,   17, 0x05,
      96,   17,   17,   17, 0x05,
     121,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     130,   17,   17,   17, 0x0a,
     137,   17,   17,   17, 0x0a,
     147,   17,   17,   17, 0x0a,
     160,   17,   17,   17, 0x0a,
     171,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TangoSettingsWin[] = {
    "TangoSettingsWin\0\0setting\0"
    "settingChanged(QVariant)\0settingChangedI(int)\0"
    "settingChangedD(double)\0"
    "settingChangedS(QString)\0cancel()\0"
    "onOk()\0onOkInt()\0onOkDouble()\0onOkBool()\0"
    "onCancel()\0"
};

void TangoSettingsWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TangoSettingsWin *_t = static_cast<TangoSettingsWin *>(_o);
        switch (_id) {
        case 0: _t->settingChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->settingChangedI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->settingChangedD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->settingChangedS((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->cancel(); break;
        case 5: _t->onOk(); break;
        case 6: _t->onOkInt(); break;
        case 7: _t->onOkDouble(); break;
        case 8: _t->onOkBool(); break;
        case 9: _t->onCancel(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TangoSettingsWin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TangoSettingsWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TangoSettingsWin,
      qt_meta_data_TangoSettingsWin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TangoSettingsWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TangoSettingsWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TangoSettingsWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TangoSettingsWin))
        return static_cast<void*>(const_cast< TangoSettingsWin*>(this));
    return QWidget::qt_metacast(_clname);
}

int TangoSettingsWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TangoSettingsWin::settingChanged(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TangoSettingsWin::settingChangedI(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TangoSettingsWin::settingChangedD(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TangoSettingsWin::settingChangedS(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TangoSettingsWin::cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
