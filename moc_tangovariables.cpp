/****************************************************************************
** Meta object code from reading C++ file 'tangovariables.h'
**
** Created: Tue Aug 14 09:45:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tangovariables.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tangovariables.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TangoVariables[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      25,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   15,   15,   15, 0x0a,
      52,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TangoVariables[] = {
    "TangoVariables\0\0cancel()\0setVar(QStringList)\0"
    "onOk()\0onCancel()\0"
};

void TangoVariables::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TangoVariables *_t = static_cast<TangoVariables *>(_o);
        switch (_id) {
        case 0: _t->cancel(); break;
        case 1: _t->setVar((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->onOk(); break;
        case 3: _t->onCancel(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TangoVariables::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TangoVariables::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TangoVariables,
      qt_meta_data_TangoVariables, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TangoVariables::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TangoVariables::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TangoVariables::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TangoVariables))
        return static_cast<void*>(const_cast< TangoVariables*>(this));
    return QWidget::qt_metacast(_clname);
}

int TangoVariables::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TangoVariables::cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TangoVariables::setVar(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
