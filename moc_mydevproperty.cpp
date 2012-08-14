/****************************************************************************
** Meta object code from reading C++ file 'mydevproperty.h'
**
** Created: Tue Aug 14 09:45:52 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mydevproperty.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mydevproperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyDevProperty[] = {

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
      15,   14,   14,   14, 0x05,
      32,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   45,   14,   14, 0x0a,
      68,   45,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyDevProperty[] = {
    "MyDevProperty\0\0setVal(QVariant)\0"
    "repaint(int)\0val\0setValue(QVariant)\0"
    "setAttrName(QString)\0"
};

void MyDevProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyDevProperty *_t = static_cast<MyDevProperty *>(_o);
        switch (_id) {
        case 0: _t->setVal((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: _t->repaint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setValue((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->setAttrName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyDevProperty::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyDevProperty::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyDevProperty,
      qt_meta_data_MyDevProperty, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyDevProperty::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyDevProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyDevProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyDevProperty))
        return static_cast<void*>(const_cast< MyDevProperty*>(this));
    return QObject::qt_metacast(_clname);
}

int MyDevProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MyDevProperty::setVal(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyDevProperty::repaint(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_Scale[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,    7,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Scale[] = {
    "Scale\0\0val\0setValue(QVariant)\0"
};

void Scale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Scale *_t = static_cast<Scale *>(_o);
        switch (_id) {
        case 0: _t->setValue((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Scale::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Scale::staticMetaObject = {
    { &MyDevProperty::staticMetaObject, qt_meta_stringdata_Scale,
      qt_meta_data_Scale, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Scale::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Scale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Scale::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Scale))
        return static_cast<void*>(const_cast< Scale*>(this));
    return MyDevProperty::qt_metacast(_clname);
}

int Scale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyDevProperty::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
